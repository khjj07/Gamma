#include "stdafx.h"

using namespace GammaEngine;

vector<GameObject*> GammaEngine::ObjectManager::addBuffer;
vector<GameObject*> GammaEngine::ObjectManager::removeBuffer;//제거될 
GammaEngine::ObjectManager::ObjectManager()
{

}

GammaEngine::ObjectManager::~ObjectManager()
{

}

void GammaEngine::ObjectManager::Frame()
{
	if (!addBuffer.empty())
	{
		for (auto iter = addBuffer.begin(); iter < addBuffer.end(); iter++)
		{
			SceneManager::currentScene->Add(*iter);
		}
		addBuffer.clear();
	}//오브젝트 생성

	if (!removeBuffer.empty())
	{
		for (auto iter = removeBuffer.begin(); iter < removeBuffer.end(); iter++)
		{
			SceneManager::currentScene->Remove(*iter);
		}
		removeBuffer.clear();
	}//오브젝트 제거
}

void GammaEngine::ObjectManager::Instantiate(GameObject* obj)
{
	addBuffer.push_back(obj);
}

void GammaEngine::ObjectManager::Destroy(GameObject* obj)
{
	removeBuffer.push_back(obj);
}

void GammaEngine::Instantiate(GameObject* obj)
{
	ObjectManager::Instantiate(obj);
}

void GammaEngine::Destroy(GameObject* obj)
{
	ObjectManager::Destroy(obj);
}


bool GammaEngine::CompareTag(GameObject* obj, string str)
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


bool GammaEngine::CompareTag(GameObject* obj, char* str)
{
	if (strcmp(obj->tag.c_str(), str) == 0)
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
	for (iter = strList.begin(); iter < strList.end(); iter++)
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