#include "stdafx.h"
#include "BoxScript.h"

BoxScript::BoxScript(GameObject* t) :Component(t)
{
}

BoxScript::~BoxScript()
{
}

void BoxScript::Start()
{

}

void BoxScript::Update()
{
	transform->position += velocity * Time::deltaTime;
	//velocity += gravity;
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{
	
}

void BoxScript::OnCollisionStay(CollisionResponse response)
{

}


void BoxScript::OnCollisionExit(CollisionResponse response)
{

}