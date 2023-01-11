#include "GammaEngine.h"
#include "CursorSript.h"
#include "Box.h"
#include "Circle.h"
using namespace GammaEngine;

CursorSript::CursorSript(GameObject* t):Component(t)
{

}

CursorSript::~CursorSript()
{
}
void CursorSript::Start()
{

}

void CursorSript::Update()
{
	vector2 mousePos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	transform->position = mousePos;

	if (Input::GetMouseButtonDown(0))
	{
		switch (mode)
		{
		case CreateMode::box :
		{
			GameObject* box = new Box();
			Instantiate(box);
			box->transform->position = mousePos;

			break;
		}
		case CreateMode::circle:
		{
			GameObject* circle = new Circle();
			Instantiate(circle);
			circle->transform->position = mousePos;
			break;
		}
		default:
			break;
		}
	}

	if (Input::GetKeyDown(VK_SPACE))
	{
		switch (mode)
		{
		case CreateMode::box:
			mode = CreateMode::circle;
			break;
		case CreateMode::circle:
			mode = CreateMode::box;
			break;
		default:
			break;
		}
	}

}
