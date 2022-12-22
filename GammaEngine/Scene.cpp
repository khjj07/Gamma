#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::Scene::Scene()
{

}

GammaEngine::Scene::~Scene()
{

}

void GammaEngine::Scene::Start()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->Start();
	}
}

void GammaEngine::Scene::Frame()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->Update();
	}
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->LateUpdate();
	}
}

void GammaEngine::Scene::OnDestroy()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		(*gameObjectIter)->OnDestroy();
	}
}

void GammaEngine::Scene::OnDisable()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->OnDisable();
	}
}

void GammaEngine::Scene::OnEnable()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->OnEnable();
	}
}

void GammaEngine::Scene::Enable()
{
	for (holdIter=holdList.begin(); holdIter < holdList.end(); holdIter++)
	{
		(*holdIter)();
	}
	OnEnable();
}

void GammaEngine::Scene::Disable()
{
	OnDisable();
	OnDestroy();
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		delete (*gameObjectIter);
	}
}

void GammaEngine::Scene::Add(GameObject* obj)
{
	gameObjectList.push_back(obj);
	obj->isEnabled = true;
	obj->OnEnable();
}

void GammaEngine::Scene::Remove(GameObject* obj)
{
	gameObjectList.erase(remove_if(gameObjectList.begin(), gameObjectList.end(), [obj](GameObject* x) { if (x == obj) return true; else return false; }), gameObjectList.end());
	obj->OnDisable();
	obj->OnDestroy();
	delete obj;
}