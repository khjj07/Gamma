#include "GammaEngine.h"
#include "Cam1.h"
#include "Cam1Script.h"
using namespace GammaEngine;

Cam1::Cam1()
{
	AddComponent<Camera>();
	AddComponent<Cam1Script>();
}