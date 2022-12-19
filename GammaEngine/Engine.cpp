#include "stdafx.h"

Engine::Engine()
{
	
}

Engine::~Engine()
{

}

void Engine::Initialize(Scene* scene)
{
	currentScene = scene;
	currentScene->Enable();
}

bool Engine::Frame()
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
	}//오브젝트 생성

	if (!removeBuffer.empty())
	{
		for (gameObjectIter = removeBuffer.begin(); gameObjectIter < removeBuffer.end(); gameObjectIter++)
		{
			currentScene->Remove(*gameObjectIter);
		}
		removeBuffer.clear();
	}//오브젝트 제거

	if (nextScene)
	{
		currentScene->Disable();
		currentScene = nextScene;
		currentScene->Enable();
		nextScene = nullptr;
	}//씬 변경

	timer->Frame();
	collisionSystem->Frame();
	currentScene->Start();
	currentScene->Frame();
	input->Frame();
	graphic->Frame();
	return true;
}

void Instantiate(GameObject* obj)
{
	Engine* engine = Engine::Instance();
	engine->addBuffer.push_back(obj);
}

void Destroy(GameObject* obj)
{
	Engine* engine = Engine::Instance();
	engine->removeBuffer.push_back(obj);
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