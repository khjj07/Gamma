#include "GammaEngine.h"
#include "Circle.h"
#include "CircleScript.h"
using namespace GammaEngine;

Circle::Circle()
{
	AddComponent<CircleCollider>();
	AddComponent<CircleScript>();
	GetComponent<CircleCollider>()->radius = 40;
	AddComponent<EllipseRenderer>();
	GetComponent<EllipseRenderer>()->size = vector2(80, 80);
	tag = string("box");
}