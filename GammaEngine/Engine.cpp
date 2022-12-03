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
	currentScene->Start();
	currentScene->Update();
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