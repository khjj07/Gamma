#include "stdafx.h"

TCHAR* ToTCHAR(string& s)
{
	tstring tstr;
	size_t cn;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs_s(&cn, t, len, all, len);
	return (TCHAR*)t;
}