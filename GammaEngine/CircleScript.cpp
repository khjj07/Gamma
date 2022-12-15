#include "stdafx.h"
#include "CircleScript.h"

CircleScript::CircleScript()
{
}

CircleScript::CircleScript(GameObject* t) :Component(t)
{
}

CircleScript::~CircleScript()
{
}

void CircleScript::Start()
{

}

void CircleScript::Update()
{
	transform->position += velocity * Time::deltaTime;
	//velocity += gravity;
	correction = vector2();
}

void CircleScript::OnCollisionEnter(CollisionResponse response)
{
	
}

void CircleScript::OnCollisionStay(CollisionResponse response)
{
	transform->GetComponent<EllipseRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Blue, 1);
}


void CircleScript::OnCollisionExit(CollisionResponse response)
{
	transform->GetComponent<EllipseRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Black, 1);
}