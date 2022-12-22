#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Engine::Engine()
{
	
}

GammaEngine::Engine::~Engine()
{

}

void GammaEngine::Engine::Initialize(Scene* scene)
{
	currentScene = scene;
	currentScene->Enable();
}

bool GammaEngine::Engine::Frame()
{
	CollisionSystem* collisionSystem = CollisionSystem::Instance();
	GraphicSystem* graphic = GraphicSystem::Instance();
	Timer* timer = Timer::Instance();
	Input* input = Input::Instance();

	if (!addBuffer.empty())
	{
		for (gameObjectIter = addBuffer.begin(); gameObjectIter < addBuffer.end(); gameObjectIter++)
		{
			currentScene->Add(* gameObjectIter);
		}
		addBuffer.clear();
	}//������Ʈ ����

	if (!removeBuffer.empty())
	{
		for (gameObjectIter = removeBuffer.begin(); gameObjectIter < removeBuffer.end(); gameObjectIter++)
		{
			currentScene->Remove(*gameObjectIter);
		}
		removeBuffer.clear();
	}//������Ʈ ����

	if (nextScene)
	{
		currentScene->Disable();
		currentScene = nextScene;
		currentScene->Enable();
		nextScene = nullptr;
	}//�� ����

	timer->Frame();
	collisionSystem->Frame();
	currentScene->Start();
	currentScene->Frame();
	input->Frame();
	graphic->Frame();
	return true;
}

void GammaEngine::Instantiate(GameObject* obj)
{
	Engine* engine = Engine::Instance();
	engine->addBuffer.push_back(obj);
}

void GammaEngine::Destroy(GameObject* obj)
{
	Engine* engine = Engine::Instance();
	engine->removeBuffer.push_back(obj);
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