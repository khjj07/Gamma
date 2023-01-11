#include "GammaEngine.h"
#include "Box2Script.h"
using namespace GammaEngine;

Box2Script::Box2Script(GameObject* t) :Component(t)
{
}

Box2Script::~Box2Script()
{
}

void Box2Script::Start()
{
	
}

void Box2Script::Update()
{
	if (Input::GetKey('W'))
	{
		transform->position.y -= 100 * Time::deltaTime;
	}
	if (Input::GetKey('S'))
	{
		transform->position.y += 100 * Time::deltaTime;
	}
	if (Input::GetKey('A'))
	{
		transform->position.x -= 100 * Time::deltaTime;
	}
	if (Input::GetKey('D'))
	{
		transform->position.x += 100 * Time::deltaTime;
	}
	if (Input::GetKey('Q'))
	{
		transform->rotation -= 100 * Time::deltaTime;
	}
	if (Input::GetKey('E'))
	{
		transform->rotation += 100 * Time::deltaTime;
	}
}

void Box2Script::LateUpdate()
{
	
}

void Box2Script::OnCollisionStay(CollisionResponse response)
{
	GetComponent<RectangleRenderer>()->SetPen(vector4(1, 0, 0, 1));
}

void Box2Script::OnCollisionExit(CollisionResponse response)
{
	GetComponent<RectangleRenderer>()->SetPen(vector4(0, 0, 0, 1));
}