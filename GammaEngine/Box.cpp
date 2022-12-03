#include "stdafx.h"
#include "Box.h"

Box::Box()
{
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->bounds = vector2(100, 100);
	AddComponent<RectangleRenderer>();
	transform->position.x = 300;
	transform->position.y = 300;
}