#pragma once
#include <tchar.h>

#define PI	3.141592654

using namespace std;

class GameObject;

typedef basic_string<TCHAR> tstring;

TCHAR* ToTCHAR(string& s);
bool CompareTag(GameObject* gameObject, string tag);//태그가 일치하면 true 반환
bool CompareTag(GameObject* gameObject, char* tag);//태그가 일치하면 true 반환
bool CompareTags(GameObject* gameObject, vector<string> tags);//태그가 하나라도 일치하면 true 반환
bool CompareTags(GameObject* gameObject, vector<char*> tags);//태그가 하나라도 일치하면 true 반환