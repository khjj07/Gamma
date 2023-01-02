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
	AddComponent<Animation>();
	GetComponent<BitmapRenderer>()->LoadBitmapImage(wstring(L"m1\\1.png"));
	GetComponent<BitmapRenderer>()->size = vector2(100, 100);
	GetComponent<Animation>()->AddFrame(L"m1\\1.png");
	GetComponent<Animation>()->AddFrame(L"m1\\2.png");
	GetComponent<Animation>()->AddFrame(L"m1\\3.png");
	tag = string("box");
}