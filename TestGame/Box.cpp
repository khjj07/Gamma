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


	//AddComponent<PolygonRenderer>();
	//GetComponent<PolygonRenderer>()->SetPoints(points);
	//GetComponent<PolygonRenderer>()->MakePolygon(wstring(L"triangle"));
	AddComponent<RectangleRenderer>();
	GetComponent<RectangleRenderer>()->size=vector2(50,50);


	//AddComponent<PolygonCollider>();
	//GetComponent<PolygonCollider>()->SetPoints(points);
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetBounds(vector2(50,50));


	AddComponent<Rigidbody>();
	GetComponent<Rigidbody>()->useGravity=true;
	transform->rotation = 10;
	tag = string("box");
}