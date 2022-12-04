#pragma once
#include <tchar.h>
#include <string>

#define PI	3.141592654

using namespace std;
typedef std::basic_string<TCHAR> tstring;
class GameObject;

TCHAR* ToTCHAR(string& s);
bool CompareTag(GameObject*, string);
bool CompareTag(GameObject*, char*);
bool CompareTags(GameObject*, vector<string>);
bool CompareTags(GameObject*, vector<char*>);