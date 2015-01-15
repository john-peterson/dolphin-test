#include <iostream>
#include <lzo/lzo1x.h>
#include <FileUtil.h>
#include <IniFile.h>

using namespace std;

void test_ini() {
	string s = "test.ini";
	float f = 117;
	IniFile ini;

	f *= 0.01;
	f *= 100;
	printf("%d\n", int(f));

	IniFile::Section* section = ini.GetOrCreateSection("test");
	section->Set("test", f);

	ini.Save(s);

	if (!ini.Load(s))
	{
		printf("\"%s\" not found\n", s.c_str());
		return;
	}

	section = ini.GetOrCreateSection("test");
	section->Get("test", &f);

	f *= 0.01;
	f *= 100;

	printf("%d\n", int(f));
}