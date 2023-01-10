#include "GammaEngine.h"
#include "BoxScript.h"
using namespace GammaEngine;

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
	velocity =velocity+ gravity;
    correction = vector2();
}

void BoxScript::OnCollisionStay(CollisionResponse response)
{
	if (response.other->CompareTag("box"))
	{
		transform->position = transform->position + response.normal*response.distance;
		if (vector2::Dot(velocity, response.normal) < 0)
		{
			velocity = velocity - response.normal * vector2::Dot(velocity, response.normal);
		}
	}
}

void BoxScript::OnCollisionExit(CollisionResponse response)
{
	GetComponent<RectangleRenderer>()->SetPen(vector4(0 ,0, 0, 1));
}