#include <iostream>
#include <lzo/lzo1x.h>
#include <FileUtil.h>

using namespace std;

#ifdef _WIN32
#pragma pack(push,1)
#endif
struct StateHeader
{
	u8 gameID[6];
	u32 size;
	double time;
	u8 end[3];
#ifdef _WIN32
};
#pragma pack(pop)
#else
} __attribute__((packed));
#endif

#if defined(__LZO_STRICT_16BIT)
static const u32 IN_LEN = 8 * 1024u;
#elif defined(LZO_ARCH_I086) && !defined(LZO_HAVE_MM_HUGE_ARRAY)
static const u32 IN_LEN = 60 * 1024u;
#else
static const u32 IN_LEN = 128 * 1024u;
#endif

static const u32 OUT_LEN = IN_LEN + (IN_LEN / 16) + 64 + 3;

static unsigned char __LZO_MMODEL out[OUT_LEN];

#define HEAP_ALLOC(var, size) \
	lzo_align_t __LZO_MMODEL var[((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

template <typename T>
void swap_write(File::IOFile *f, T data)
{
	// change byte order
	if (sizeof(data) == 4)
		data = Common::swap32(data);
	else
		data = Common::swap64(data);

	// write
	f->WriteArray(&data, 1);

	// restore byte order
	data = Common::swap32(data);
}

void decompress(const std::string& filename) {
	//printf("src_len %u\n", sizeof(lzo_uint));

	bool no_header = true;

	File::IOFile f(filename, "rb");
	if (!f) {
		printf("File not found\n");
		return;
	}

	StateHeader header;
	std::vector<u8> buffer;
	if (no_header)
		header.size = 0;
	else {
		f.ReadArray(&header, 1);
		printf("Size: %u, tell %llu\n", header.size, f.Tell());
	}

	if (!no_header)
		buffer.resize(header.size);

	lzo_uint i = 0;
	while (true) {
		lzo_uint32 src_len = 0;  // number of bytes to read
		lzo_uint32 dst_len = 0;  // number of bytes to write

		if (!f.ReadArray(&dst_len, 1))
			break;
		dst_len = Common::swap32(dst_len);

		if (!f.ReadArray(&src_len, 1))
			break;
		src_len = Common::swap32(src_len);

		if (no_header)
			buffer.resize(buffer.size() + dst_len);

        if (src_len < dst_len)
        {
			lzo_uint d = dst_len;

			f.ReadBytes(out, src_len);
			const int res = lzo1x_decompress(out, src_len, &buffer[i], &d, NULL);
			if (res != LZO_E_OK) {
				printf("Internal LZO Error - decompression failed (%d) (%li, %li)\n", res, i, dst_len);
				return;
			}
		}
		else
		{
			_assert_(dst_len == src_len);
			//memcpy(&buffer[i], out, src_len);
			f.ReadBytes(&buffer[i], src_len);
		}

		printf("i %8d, src_len %u, dst_len %u\n", i, src_len, dst_len);
		i += dst_len;
		if (no_header)
			buffer.resize(i);
	}

	// all good

	//std::string filename_out = "uncompressed.bin";
	std::string filename_out = "uncompressed.rar";
	File::IOFile g(filename_out, "wb");
	g.WriteArray(&buffer[0], buffer.size());
	//g.WriteBytes(buffer, buffer.size());

	printf("decompressed: %s\n", ArrayToString(&buffer[0], buffer.size() > 8 ? 8 : buffer.size()).c_str());
}

void compress(std::string& filename)
{
	if (!File::Exists(filename)) {
		printf("file missing: %s\n", filename.c_str());
		return;
	}

	std::vector<u8> buffer_vector(File::GetSize(filename));

	File::IOFile g(filename, "rb");
	g.ReadArray(&buffer_vector[0], File::GetSize(filename));

	//printf("data: %s\n", ArrayToString(&buffer_vector[0], buffer_vector.size()).c_str());

	const u8* const buffer_data = &buffer_vector[0];
	const size_t buffer_size = buffer_vector.size();

	//printf("data: %s\n", ArrayToString(buffer_data, buffer_size).c_str());

	std::string base, ext;
	SplitPath(filename, NULL, &base, &ext);
	filename = base + ".lzo";
	File::IOFile f(filename, "wb");
	if (!f)
	{
		printf("Could not save state\n");
		return;
	}

	// define
	//printf("%s\n", LZO_);

	// size
	printf(
		"LZO_SIZEOF_INT %u"
		"\nLZO_SIZEOF_LONG %u"
		"\nLZO_SIZEOF_VOID_P %u"
		"\nunsigned long %u"
		"\nlzo_uint %u"
		"\nlzo_uint32 %u"
		"\n"
		, LZO_SIZEOF_INT
		, LZO_SIZEOF_LONG
		, LZO_SIZEOF_VOID_P
		, sizeof(unsigned long)
		, sizeof(lzo_uint)
		, sizeof(lzo_uint32)
		);

	// Setting up the header
	//StateHeader header;
	//memcpy(header.gameID, SConfig::GetInstance().m_LocalCoreStartupParameter.GetUniqueID().c_str(), 6);
	//header.size = g_use_compression ? buffer_size : 0;
	//header.time = Common::Timer::GetDoubleTime();
	//memcpy(header.end, "EOH", 3);

	//f.WriteArray(&header, 1);

	//if (0 != header.size)	// non-zero header size means the state is compressed
	{
		lzo_uint i = 0;
		while (true)
		{
			//lzo_uint src_len = 0;
			lzo_uint32 src_len = 0;
			lzo_uint dst_len = 0;
			//lzo_uint32 dst_len = 0;

			if ((i + IN_LEN) >= buffer_size)
				src_len = buffer_size - i;
			else
				src_len = IN_LEN;

			if (lzo1x_1_compress(buffer_data + i, src_len, out, &dst_len, wrkmem) != LZO_E_OK)
				printf("Internal LZO Error - compression failed\n");

			printf("i %8d, src_len %u, dst_len %u\n", i, src_len, dst_len);

			// write length
			swap_write(&f, src_len);
			printf("i %8d, src_len %lu, sizeof %u\n", i, src_len, sizeof(src_len));

			// the size of the data to write is 'dst_len'
			if (dst_len < src_len) {
				swap_write(&f, dst_len);
				f.WriteBytes(out, dst_len);
			}
			// write uncompressed data
			else {
				f.WriteArray(&dst_len, 1);
				//f.WriteArray((lzo_uint32*)&dst_len, 1);
				//swap_write(&f, src_len);
				f.WriteBytes(buffer_data + i, src_len);
			}

			if (src_len != IN_LEN)
				break;

			i += src_len;
		}

		// EOF
		u8 zero[4] = {0};
		f.WriteBytes(&zero, 4);
	}
	//else	// uncompressed
	//{
	//	f.WriteBytes(buffer_data, buffer_size);
	//}

	printf("Saved State to %s\n", filename.c_str());
}

void test_lzop() {
	//std::string filename = "C:/Users/User/Downloads/state/GCTE51.s05";
	//std::string filename = "C:/Users/User/Downloads/state/trimmed.sav";
	//std::string filename = "file.lzo";
	//std::string filename = "large.lzo";
	//decompress(filename);

	std::string filename_compress = "file.bin";
	//std::string filename_compress = "file.rar";
	//std::string filename_compress = "large.rar";
	compress(filename_compress);

	printf("done\n");
	std::cin.get();
}