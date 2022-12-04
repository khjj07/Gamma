#include "stdafx.h"

Engine::Engine()
{
	
}


void Engine::Initialize(Scene* scene)
{
	currentScene = scene;
	currentScene->Enable();

}


bool Engine::Frame()
{
	DirectXModule* dxModule = DirectXModule::Instance();
	CollisionSystem* collisionSystem = CollisionSystem::Instance();
	Timer* timer = Timer::Instance();

	Input* input = Input::Instance();
	
	if (!addBuffer.empty())
	{
		for (gameObjectIter = addBuffer.begin(); gameObjectIter < addBuffer.end(); gameObjectIter++)
		{
			currentScene->Add(* gameObjectIter);
		}
		addBuffer.clear();
	}
	if (!removeBuffer.empty())
	{
		for (gameObjectIter = removeBuffer.begin(); gameObjectIter < removeBuffer.end(); gameObjectIter++)
		{
			currentScene->Remove(*gameObjectIter);
		}
		removeBuffer.clear();
	}
	if (nextScene)
	{
		currentScene->Disable();
		currentScene = nextScene;
		currentScene->Enable();
		nextScene = nullptr;
	}
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