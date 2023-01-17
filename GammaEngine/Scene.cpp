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
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->Start();
	}
}

void GammaEngine::Scene::Frame()
{
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->Update();
	}

	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->LateUpdate();
	}
}

void GammaEngine::Scene::OnDestroy()
{
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		(*iter)->OnDestroy();
	}
}

void GammaEngine::Scene::OnDisable()
{
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		if ((*iter)->isEnabled)
			(*iter)->OnDisable();
	}
}

void GammaEngine::Scene::OnEnable()
{
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		if((*iter)->isEnabled)
			(*iter)->OnEnable();
	}
}

void GammaEngine::Scene::Enable()
{
	for (auto iter =holdList.begin(); iter < holdList.end(); iter++)
	{
		GameObject* newObj = new GameObject(**iter);
		Add(newObj);
	}
	OnEnable();
}

void GammaEngine::Scene::Disable()
{
	OnDisable();
	OnDestroy();
	for (auto iter = gameObjectList.begin(); iter < gameObjectList.end(); iter++)
	{
		delete (*iter);
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
void GammaEngine::Scene::Hold(GameObject* obj)
{
	GameObject* newObj = new GameObject(*obj);
	holdList.push_back(newObj);
};