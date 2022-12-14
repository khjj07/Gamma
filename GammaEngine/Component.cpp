#include "stdafx.h"

Component::Component()
{

}

Component::Component(GameObject* g)
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

void Component::Render()
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