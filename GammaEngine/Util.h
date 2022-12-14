#pragma once
#include <tchar.h>

#define PI	3.141592654

using namespace std;

class GameObject;

typedef basic_string<TCHAR> tstring;

TCHAR* ToTCHAR(string& s);
bool CompareTag(GameObject* gameObject, string tag);//�±װ� ��ġ�ϸ� true ��ȯ
bool CompareTag(GameObject* gameObject, char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
bool CompareTags(GameObject* gameObject, vector<string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
bool CompareTags(GameObject* gameObject, vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ