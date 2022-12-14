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
	DirectXModule* dxModule = DirectXModule::Instance();
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
	dxModule->Render();
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