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
	transform->GetComponent<RectangleRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Blue, 1);
}

void BoxScript::OnCollisionStay(CollisionResponse response)
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


void BoxScript::OnCollisionExit(CollisionResponse response)
{
	transform->GetComponent<RectangleRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Black, 1);
}