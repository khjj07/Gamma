#include "stdafx.h"
#include "Box2Script.h"

Box2Script::Box2Script()
{
}

Box2Script::Box2Script(Transform* t) :Component(t)
{
}

Box2Script::~Box2Script()
{
}

void Box2Script::Start()
{
	//Tween::Animate(transform->rotation, PLAYBACK::LOOP_PINGPONG, 70,EASING::INOUTBOUNCE,10);
	//transform->rotation = 90;
	
}

void Box2Script::Update()
{
	transform->GetComponent<LineRenderer>()->src = vector2();
	transform->GetComponent<LineRenderer>()->dst = vector2();
	if (Input::GetKey('A'))
	{
		transform->position.x -= 300 * Time::deltaTime;
	}
	if (Input::GetKey('D'))
	{
		transform->position.x += 300 * Time::deltaTime;
	}

	if (Input::GetKey('W'))
	{
		transform->position.y -= 300 * Time::deltaTime;
	}
	if (Input::GetKey('S'))
	{
		transform->position.y += 300 * Time::deltaTime;
	}
}

void Box2Script::LateUpdate()
{
	
}

void Box2Script::OnCollisionEnter(CollisionResponse response)
{
	if (response.other->CompareTag(string("box")))
	{
		transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Blue, 1);
	}
}

void Box2Script::OnCollisionExit(CollisionResponse response)
{
	if (response.other->CompareTag(string("box")))
	{
		transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Black, 1);
	}
}