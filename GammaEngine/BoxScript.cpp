#include "stdafx.h"
#include "BoxScript.h"

BoxScript::BoxScript()
{
}

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
	transform->position += velocity*Time::deltaTime;
	//velocity += gravity;
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{
	
}

void BoxScript::OnCollisionStay(CollisionResponse response)
{
	transform->GetComponent<RectangleRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Blue, 1);
}


void BoxScript::OnCollisionExit(CollisionResponse response)
{
	transform->GetComponent<RectangleRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Black, 1);
}