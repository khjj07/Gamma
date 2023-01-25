#include "stdafx.h"

using namespace GammaEngine;

vector<GameObject*>* GammaEngine::ObjectManager::addBuffer;
vector<GameObject*>* GammaEngine::ObjectManager::removeBuffer;//제거될 
GammaEngine::ObjectManager::ObjectManager()
{
	addBuffer = new vector<GameObject*>();
	removeBuffer = new vector<GameObject*>();
}

GammaEngine::ObjectManager::~ObjectManager()
{

}

void GammaEngine::ObjectManager::Frame()
{
	if (!addBuffer->empty())
	{
		for (auto iter = addBuffer->begin(); iter < addBuffer->end(); iter++)
		{
			SceneManager::currentScene->Add(*iter);
		}
		addBuffer->clear();
	}//오브젝트 생성

	if (!removeBuffer->empty())
	{
		for (auto iter = removeBuffer->begin(); iter < removeBuffer->end(); iter++)
		{
			SceneManager::currentScene->Remove(*iter);
		}
		removeBuffer->clear();
	}//오브젝트 제거
}

void GammaEngine::ObjectManager::Instantiate(GameObject* obj)
{
	addBuffer->push_back(obj);
}

void GammaEngine::ObjectManager::Destroy(GameObject* obj)
{
	removeBuffer->push_back(obj);
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
	return obj->CompareTag(str);
}


bool GammaEngine::CompareTag(GameObject* obj, char* str)
{
	return obj->CompareTag(str);
}

bool GammaEngine::CompareTags(GameObject* obj, vector<string> strList)
{
	return obj->CompareTags(strList);
}


bool GammaEngine::CompareTags(GameObject* obj, vector<char*> strList)
{
	return obj->CompareTags(strList);
}