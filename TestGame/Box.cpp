#include "GammaEngine.h"
#include "Box.h"
#include "BoxScript.h"
using namespace GammaEngine;

Box::Box()
{
	AddComponent<BoxCollider>();
	AddComponent<BoxScript>();
	GetComponent<BoxCollider>()->SetBounds(vector2(80, 80));
	AddComponent<RectangleRenderer>();
	GetComponent<RectangleRenderer>()->size=vector2(80, 80);
	AddComponent<Animation>();


	tag = string("box");
}