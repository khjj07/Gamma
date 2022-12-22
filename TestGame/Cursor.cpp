#include "GammaEngine.h"
#include "Cursor.h"
#include "CursorSript.h"
using namespace GammaEngine;

Cursor::Cursor()
{
	AddComponent<CursorSript>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->bounds = vector2(10, 10);
	tag = string("box");
}

Cursor::~Cursor()
{
}