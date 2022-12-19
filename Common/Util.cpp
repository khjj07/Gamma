#include "Util.h"
#include <tchar.h>
#include <string>
#include <locale.h>
using namespace std;

TCHAR* ToTCHAR(string& s)
{
	static wchar_t* t=nullptr;
	tstring tstr;
	size_t cn;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	if (t)
	{
		delete t;
	}
	t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	setlocale(LC_ALL, "");
	mbstowcs_s(&cn, t, len, all, len);
	return (TCHAR*)t;
}
