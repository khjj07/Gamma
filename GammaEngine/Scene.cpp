#include "stdafx.h"


Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::Start()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->Start();
	}
}

void Scene::Frame()
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

void Scene::OnDestroy()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		(*gameObjectIter)->OnDestroy();
	}
}

void Scene::OnDisable()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if ((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->OnDisable();
	}
}

void Scene::OnEnable()
{
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		if((*gameObjectIter)->isEnabled)
			(*gameObjectIter)->OnEnable();
	}
}

void Scene::Enable()
{
	for (holdIter=holdList.begin(); holdIter < holdList.end(); holdIter++)
	{
		(*holdIter)();
	}
	OnEnable();
}

void Scene::Disable()
{
	OnDisable();
	OnDestroy();
	for (gameObjectIter = gameObjectList.begin(); gameObjectIter < gameObjectList.end(); gameObjectIter++)
	{
		delete (*gameObjectIter);
	}
}

void Scene::Add(GameObject* obj)
{
	gameObjectList.push_back(obj);
	obj->isEnabled = true;
	obj->OnEnable();
}

void Scene::Remove(GameObject* obj)
{
	gameObjectList.erase(remove_if(gameObjectList.begin(), gameObjectList.end(), [obj](GameObject* x) { if (x == obj) return true; else return false; }), gameObjectList.end());
	obj->OnDisable();
	obj->OnDestroy();
	delete obj;
}