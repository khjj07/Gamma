#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Engine::Engine()
{
	
}

GammaEngine::Engine::~Engine()
{

}

void GammaEngine::Engine::Initialize()
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	Input* input = Input::Instance();
	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();
	graphic->Initialize(WindowSystem::hWnd);
	input->Initialize(WindowSystem::hWnd);

	SceneManager::currentScene->Enable();
}

bool GammaEngine::Engine::Frame()
{
	CollisionSystem* collisionSystem = CollisionSystem::Instance();
	GraphicSystem* graphic = GraphicSystem::Instance();
	Timer* timer = Timer::Instance();
	Input* input = Input::Instance();

	ObjectManager::Frame();
	timer->Frame();
	collisionSystem->Frame();
	SceneManager::currentScene->Start();
	SceneManager::currentScene->Frame();
	input->Frame();
	graphic->Frame();
	return true;
}
