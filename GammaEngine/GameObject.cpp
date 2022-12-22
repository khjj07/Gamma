#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::GameObject::GameObject()
{
	transform = new Transform(this);
}

GammaEngine::GameObject::~GameObject()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		delete	(*componentIter);
	}
	componentList.clear();
	delete transform;
}

void GammaEngine::GameObject::Start()
{
	if (!isStarted)
	{
		for (componentIter= componentList.begin(); componentIter < componentList.end(); componentIter++)
		{
			(*componentIter)->Start();
		}
		isStarted = true;
	}
}

void GammaEngine::GameObject::Update()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->Update();
	}
}

void GammaEngine::GameObject::LateUpdate()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->LateUpdate();
	}
}


void GammaEngine::GameObject::OnDestroy()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnDestroy();
	}
}

void GammaEngine::GameObject::OnDisable()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnDisable();
	}
}

void GammaEngine::GameObject::OnEnable()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnEnable();
	}
}

void GammaEngine::GameObject::OnCollisionEnter(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionEnter(response);
	}
}

void GammaEngine::GameObject::OnCollisionStay(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionStay(response);
	}
}

void GammaEngine::GameObject::OnCollisionExit(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionExit(response);
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
