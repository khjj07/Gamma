#include "stdafx.h"

GameObject::GameObject()
{
	transform = new Transform(this);
}

GameObject::~GameObject()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		delete	(*componentIter);
	}
	componentList.clear();
	delete transform;
}

void GameObject::Start()
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

void GameObject::Update()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->Update();
	}
}

void GameObject::LateUpdate()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->LateUpdate();
	}
}


void GameObject::OnDestroy()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnDestroy();
	}
}

void GameObject::OnDisable() 
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnDisable();
	}
}

void GameObject::OnEnable()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnEnable();
	}
}

void GameObject::OnCollisionEnter(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionEnter(response);
	}
}

void GameObject::OnCollisionStay(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionStay(response);
	}
}

void GameObject::OnCollisionExit(CollisionResponse response)
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionExit(response);
	}
}

bool GameObject::CompareTag(string str)
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

bool GameObject::CompareTag(char* str)
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

bool GameObject::CompareTags(vector<string> strList)
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

bool GameObject::CompareTags(vector<char*> strList)
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
