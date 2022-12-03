#include "stdafx.h"
#include "TestScript.h"

TestScript::TestScript()
{
}

TestScript::TestScript(Transform* t):Component(t)
{
}

TestScript::~TestScript()
{
}

void TestScript::Update()
{
	float speed = 100;
	vector2 pos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	char str[100];
	sprintf_s(str, "x:%.2f  y:%.2f \n x:%.2f  y:%.2f",pos.x- Input::GetMousePosition().x,pos.y- Input::GetMousePosition().y, Input::GetMousePosition().x, Input::GetMousePosition().y);

	transform->GetComponent<TextRenderer>()->text = string(str);
	transform->position = pos;
	//transform->GetComponent<FillEllipseRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Blue, 1);
}

void TestScript::OnCollisionEnter()
{
	transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Red, 1);
}

void TestScript::OnCollisionExit()
{
	transform->GetComponent<RectangleRenderer>()->SetBrush<ID2D1SolidColorBrush>(ColorF::Black, 1);
}