#include "GammaEngine.h"
#include "Box.h"
#include "BoxScript.h"
using namespace GammaEngine;

Box::Box()
{
	AddComponent<BoxCollider>();
	AddComponent<BoxScript>();
	GetComponent<BoxCollider>()->bounds = vector2(80,80);
	AddComponent<RectangleRenderer>();
	GetComponent<RectangleRenderer>()->size = vector2(80, 80);
	tag = string("box");
}