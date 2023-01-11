#include "GammaEngine.h"
#include "Cursor.h"
#include "CursorSript.h"
using namespace GammaEngine;

Cursor::Cursor()
{
	AddComponent<CursorSript>();
	tag = string("cursor");
}

Cursor::~Cursor()
{
}