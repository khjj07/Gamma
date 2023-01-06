#include "GammaEngine.h"
#include "Cursor.h"
#include "CursorSript.h"
using namespace GammaEngine;

Cursor::Cursor()
{
	AddComponent<CursorSript>();
	AddComponent<BoxCollider>();
	GetComponent<BoxCollider>()->SetBounds(vector2(10, 10));
	tag = string("cursor");
}

Cursor::~Cursor()
{
}