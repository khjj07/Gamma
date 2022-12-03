#include "stdafx.h"
#include "Scene1.h"
#include "FillEllipseRenderer.h"
#include "Test.h"
#include "Cam1.h"
#include "Box.h"
Scene1::Scene1()
{
	Hold<Cam1>();
	Hold<Test>();
	Hold<Box>();
}