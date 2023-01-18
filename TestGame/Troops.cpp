#include "GammaEngine.h"
#include "Troops.h"

using namespace GammaEngine;

Troops::Troops(GameObject* t) : Component(t)
{

}

Troops::~Troops()
{

}

void Troops::Update()
{
	vector2 mousePos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	if (Input::GetMouseButtonDown(0))
	{
		startpoint = mousePos;
		drag = true;
	}

	if (drag)
	{
		endpoint = mousePos;
	}

	if (drag && Input::GetMouseButtonUp(0))
	{
		drag = false;
		startpoint = vector2();
		endpoint = vector2();
	}

	GetComponent<RectangleRenderer>()->size = (endpoint - startpoint);
	transform->position = (endpoint + startpoint) / 2;
}