#include "GammaEngine.h"
#include "Box.h"
#include "BoxScript.h"
using namespace GammaEngine;

Box::Box()
{
	AddComponent<BoxCollider>();
	AddComponent<BoxScript>();
	GetComponent<BoxCollider>()->bounds = vector2(80,80);
	AddComponent<BitmapRenderer>();
	GetComponent<BitmapRenderer>()->LoadBitmapImage(wstring(L"m1\\1.png"));
	GetComponent<BitmapRenderer>()->size = vector2(100, 100);
	tag = string("box");
}