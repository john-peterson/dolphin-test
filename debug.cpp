#include <FileUtil.h>
#include <BreakPoints.h>

using namespace std;

typedef std::vector<TMemCheck> TMemChecks;
TMemChecks m_MemChecks;

bool GetMemCheck(u32 address, u8 size)
{
	for (TMemChecks::iterator i = m_MemChecks.begin(); i != m_MemChecks.end(); ++i)
	{
		printf("%08x %08x\n", address, address + size - 1);
		if (i->bRange)
		{
			if (i->StartAddress >= address && i->EndAddress <= address + size - 1)
				return true;
		}
		else if (i->StartAddress >= address && i->StartAddress <= address + size - 1)
			return true;
	}

	// none found
	return false;
}

void test_debug() {
	TMemCheck m;
	m.bRange = false;
	m.StartAddress = 0x803785cb;

	m.bRange = true;
	m.EndAddress = 0x803785cb;

	m_MemChecks.push_back(m);


	//c8
	//c9
	//ca
	//cb

	printf(
		"%d\n"

		"%d\n"
		"%d\n"
		"%d\n"

		"%d\n"
		, GetMemCheck(0x803785c7, 4)

		, GetMemCheck(0x803785c8, 4)
		, GetMemCheck(0x803785ca, 2)
		, GetMemCheck(0x803785cb, 1)

		, GetMemCheck(0x803785cc, 1)
		);
}