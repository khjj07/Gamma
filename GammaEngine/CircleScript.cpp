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
	transform->GetComponent<EllipseRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Blue, 1);
}

void CircleScript::OnCollisionStay(CollisionResponse response)
{
	// 	vector2 comp = response.normal* response.distance;
	// 	correction = correction + comp;
	// 	transform->position += comp;
	// 	float proj = vector2::Dot(velocity, response.normal);
	// 	if (proj < 0)
	// 	{
	// 		velocity = velocity - response.normal * proj;
	// 	}
}


void CircleScript::OnCollisionExit(CollisionResponse response)
{
	transform->GetComponent<EllipseRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Black, 1);
}