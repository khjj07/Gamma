#include "GammaEngine.h"
#include "Box2Script.h"
#include "Circle.h"
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
	Rigidbody* rigidbody = GetComponent<Rigidbody>();
	if (Input::GetKey('W'))
	{
		rigidbody->ApplyForce(vector2::Up * 2000 * Time::deltaTime);
	}
	if (Input::GetKey('S'))
	{
		rigidbody->ApplyForce(vector2::Down * 2000 * Time::deltaTime);
	}
	if (Input::GetKey('A'))
	{
		rigidbody->ApplyForce(vector2::Left * 2000 * Time::deltaTime);
	}
	if (Input::GetKey('D'))
	{
		rigidbody->ApplyForce(vector2::Right * 2000 * Time::deltaTime);
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