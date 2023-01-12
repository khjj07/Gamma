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

	AddComponent<PolygonRenderer>();
	GetComponent<PolygonRenderer>()->AddPoints(vector2(- 100, -100));
	GetComponent<PolygonRenderer>()->AddPoints(vector2(100, -100));
	GetComponent<PolygonRenderer>()->AddPoints(vector2(0, 100));
	GetComponent<PolygonRenderer>()->MakePolygon(wstring(L"triangle"));
	AddComponent<Animation>();


	tag = string("box");
}