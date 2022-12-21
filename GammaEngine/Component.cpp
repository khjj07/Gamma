#include "stdafx.h"

Component::Component(GameObject* g):componentList(g->componentList)
{
	gameObject = g;
	transform = g->transform;
}

Component::~Component()
{

}


void Component::Start()
{
	
}

void Component::Update()
{
	
}
void Component::LateUpdate()
{

}

void Component::OnDestroy()
{
	
}

void Component::OnDisable()
{
	
}

void Component::OnEnable()
{

}

void Component::OnCollisionEnter(CollisionResponse response)
{

}

void Component::OnCollisionStay(CollisionResponse response)
{

}

void Component::OnCollisionExit(CollisionResponse response)
{

}