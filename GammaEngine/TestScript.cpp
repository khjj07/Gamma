#include "stdafx.h"
#include "TestScript.h"
#include "Box.h"
TestScript::TestScript()
{
}

TestScript::TestScript(GameObject* t):Component(t)
{
}

TestScript::~TestScript()
{
}
void TestScript::Start()
{
	transform->rotation = 45;
}

void TestScript::LateUpdate()
{
	transform->GetComponent<LineRenderer>()->src = transform->position;
	vector2 pos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	
	RaycastResponse  res = Physics::Raycast(transform->position, pos, string("box"));
	if (res.hit)
	{
		transform->GetComponent<LineRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Red, 1);
		transform->GetComponent<LineRenderer>()->dst = res.position;
		if (res.gameObject->GetComponent<LineRenderer>())
		{
			res.gameObject->GetComponent<LineRenderer>()->src = res.position;

			vector2 diff = res.position - transform->position;
			res.gameObject->GetComponent<LineRenderer>()->dst = res.position + vector2::Reflect(diff,res.normal) ;
		}
	}
	else
	{
		transform->GetComponent<LineRenderer>()->SetPen<ID2D1SolidColorBrush>(ColorF::Black, 1);
		transform->GetComponent<LineRenderer>()->dst = pos;
	}
	if (Input::GetMouseButtonDown(0))
	{
		GameObject* box = new Box();
		box->transform->position = pos;
		Instantiate(box);
	}
}

void TestScript::OnCollisionEnter(CollisionResponse response)
{
	if (response.other->CompareTag(string("box")))
	{
		transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Red, 1);
	}
}

void TestScript::OnCollisionExit(CollisionResponse response)
{
	if (response.other->CompareTag(string("box")))
	{
		transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Black, 1);
	}
}