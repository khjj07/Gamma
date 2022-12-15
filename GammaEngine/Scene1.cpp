#include "stdafx.h"
#include "Scene1.h"
#include "Cursor.h"
#include "Cam1.h"
#include "Box.h"
#include "Box2.h"
#include "Debug.h"

Scene1::Scene1()
{
	Hold<Cursor>();
	Hold<Debug>();
	Hold<Cam1>();
}