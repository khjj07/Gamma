#include "stdafx.h"
#include "Box.h"

Box::Box()
{
	AddComponent<CircleCollider>();
	GetComponent<CircleCollider>()->radius = 40;
	AddComponent<FillEllipseRenderer>();
	GetComponent<FillEllipseRenderer>()->size = vector2(80, 80);
	tag = string("box");
}