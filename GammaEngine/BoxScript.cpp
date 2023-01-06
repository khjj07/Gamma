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
	//velocity += gravity;
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{
	if (response.other->CompareTag("box"))
	{
		GetComponent<RectangleRenderer>()->SetPen(vector4(1, 0, 0, 1));
	}
}

void BoxScript::OnCollisionExit(CollisionResponse response)
{
	GetComponent<RectangleRenderer>()->SetPen(vector4(0 ,0, 0, 1));
}