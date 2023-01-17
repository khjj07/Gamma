#include "stdafx.h"

using namespace GammaEngine;
vector<Scene*> GammaEngine::SceneManager::sceneList;
Scene* GammaEngine::SceneManager::currentScene=NULL;

GammaEngine::SceneManager::SceneManager()
{

}

GammaEngine::SceneManager::~SceneManager()
{

}

void GammaEngine::SceneManager::Initialize()
{
	assert(sceneList[0], "Add at least one scene");
	LoadScene(0);
	currentScene->Enable();
}

void GammaEngine::SceneManager::AddScene(Scene* scene)
{
	sceneList.push_back(scene);
}

void GammaEngine::SceneManager::LoadScene(int number)
{
	if (currentScene)
	{
		currentScene->Disable();
	}
	currentScene = sceneList[number];
	currentScene->Enable();
}