#include "stdafx.h"

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
	mbstowcs_s(&cn, t, len, all, len);
	return (TCHAR*)t;
}

bool CompareTag(GameObject* obj, string str)
{
	if (obj->tag == str)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CompareTag(GameObject* obj, char* str)
{
	if (strcmp(obj->tag.c_str(), str)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CompareTags(GameObject* obj, vector<string> strList)
{
	vector<string>::iterator iter;
	for(iter=strList.begin();iter<strList.end();iter++)
	{
		if (CompareTag(obj, (*iter)))
		{
			return true;
		}
	}
	return false;
}


bool CompareTags(GameObject* obj, vector<char*> strList)
{
	vector<char*>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag(obj, (*iter)))
		{
			return true;
		}
	}
	return false;
}