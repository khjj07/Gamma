#include "stdafx.h"

GameObject::GameObject()
{
	transform = new Transform(this);
}

GameObject::~GameObject()
{
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

void GameObject::OnDestroy()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnDestroy();
		delete(*componentIter);
	}
	delete transform;
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

void GameObject::OnCollisionEnter()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionEnter();
	}
}

void GameObject::OnCollisionStay()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionStay();
	}
}

void GameObject::OnCollisionExit()
{
	for (componentIter = componentList.begin(); componentIter < componentList.end(); componentIter++)
	{
		(*componentIter)->OnCollisionExit();
	}
}