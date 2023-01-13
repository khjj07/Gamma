#include "GammaEngine.h"
#include "Box.h"
#include "BoxScript.h"
using namespace GammaEngine;

Box::Box()
{
	AddComponent<BoxScript>();

	vector<vector2> points;
	points.push_back(vector2(-100, -100));
	points.push_back(vector2(100, -100));
	points.push_back(vector2(0, 100));


	AddComponent<PolygonRenderer>();
	GetComponent<PolygonRenderer>()->SetPoints(points);
	GetComponent<PolygonRenderer>()->MakePolygon(wstring(L"triangle"));

	AddComponent<PolygonCollider>();
	GetComponent<PolygonCollider>()->SetPoints(points);

	tag = string("box");
}