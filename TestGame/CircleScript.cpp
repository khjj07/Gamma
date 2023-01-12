#include "GammaEngine.h"
#include "CircleScript.h"
using namespace GammaEngine;

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
	correction = vector2();
}

void CircleScript::OnCollisionStay(CollisionResponse response)
{
	if (response.other->CompareTag("box"))
	{
		if (vector2::Dot(velocity, response.normal) < 0)
		{
			velocity = velocity - response.normal * vector2::Dot(velocity, response.normal);
		}
		transform->position = transform->position - response.normal * (response.distance + 2);

	}
}

void CircleScript::OnCollisionExit(CollisionResponse response)
{
	GetComponent<EllipseRenderer>()->SetPen(vector4(0, 0, 0, 1));
}