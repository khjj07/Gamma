#include "GammaEngine.h"
#include "Scene1.h"
#include "Cursor.h"
#include "Cam1.h"
#include "Box.h"
#include "Box2.h"
using namespace GammaEngine;

Scene1::Scene1()
{
	Hold<Cursor>();
	Hold<Box2>();
	Hold<Cam1>();
}