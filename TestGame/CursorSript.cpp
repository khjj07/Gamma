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
		
	}
}
