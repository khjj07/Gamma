#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Engine::Engine()
{
	objectManager = new ObjectManager();
	sceneManager = new SceneManager();
}

GammaEngine::Engine::~Engine()
{

}

void GammaEngine::Engine::Initialize()
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	CollisionSystem* collisionSystem = CollisionSystem::Instance();
	Input* input = Input::Instance();
	Timer* timer = new Timer();
#ifdef DEBUG
	Debug* debug = new Debug();
#endif // DEBUG

	graphic->Initialize(WindowSystem::hWnd);
	input->Initialize(WindowSystem::hWnd);
	sceneManager->Initialize();
	collisionSystem->Initialize();
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
