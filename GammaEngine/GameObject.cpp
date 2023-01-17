#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::GameObject::GameObject()
{
	transform = new Transform(this);
}

GammaEngine::GameObject::GameObject(const GameObject& obj)
{
	transform = obj.transform;
	tag = obj.tag;
	componentList = obj.componentList;
}

GammaEngine::GameObject::~GameObject()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		delete	(*iter);
	}
	componentList.clear();
	delete transform;
}

void GammaEngine::GameObject::Start()
{
	if (!isStarted)
	{
		for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
		{
			(*iter)->Start();
		}
		isStarted = true;
	}
}

void GammaEngine::GameObject::Update()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->Update();
	}
}

void GammaEngine::GameObject::LateUpdate()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->LateUpdate();
	}
}


void GammaEngine::GameObject::OnDestroy()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnDestroy();
	}
}

void GammaEngine::GameObject::OnDisable()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnDisable();
	}
}

void GammaEngine::GameObject::OnEnable()
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnEnable();
	}
}

void GammaEngine::GameObject::OnCollisionEnter(CollisionResponse response)
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnCollisionEnter(response);
	}
}

void GammaEngine::GameObject::OnCollisionStay(CollisionResponse response)
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnCollisionStay(response);
	}
}

void GammaEngine::GameObject::OnCollisionExit(CollisionResponse response)
{
	for (auto iter = componentList.begin(); iter < componentList.end(); iter++)
	{
		(*iter)->OnCollisionExit(response);
	}
}

bool GammaEngine::GameObject::CompareTag(string str)
{
	if (this->tag == str)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GammaEngine::GameObject::CompareTag(char* str)
{
	if (strcmp(this->tag.c_str(), str)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GammaEngine::GameObject::CompareTags(vector<string> strList)
{
	vector<string>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

bool GammaEngine::GameObject::CompareTags(vector<char*> strList)
{
	vector<char*>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}
