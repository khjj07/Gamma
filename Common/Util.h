#pragma once
#include <tchar.h>
#include <string>
#include <locale.h>
using namespace std;
#define PI	3.141592654


typedef basic_string<TCHAR> tstring;

TCHAR* ToTCHAR(string& s);
