#include "GammaEngine.h"
#include "Box2.h"
#include "Box2Script.h"
using namespace GammaEngine;

Box2::Box2()
{
	AddComponent<BoxCollider>();
	AddComponent<RectangleRenderer>();
	AddComponent<LineRenderer>();
	AddComponent<Box2Script>();
	GetComponent<BoxCollider>()->SetBounds(vector2(500,100));
	GetComponent<RectangleRenderer>()->size = vector2(500, 100);
	GetComponent<RectangleRenderer>()->order = -1;

	transform->position.x = 300;
	transform->position.y = 300;
	tag = string("box");
}

Box2::~Box2()
{

}