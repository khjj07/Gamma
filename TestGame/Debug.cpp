#include "GammaEngine.h"
#include "Debug.h"
#include "DebugScript.h"
using namespace GammaEngine;

Debug::Debug()
{
	AddComponent<TextRenderer>();
	AddComponent<DebugScript>();
	GetComponent<TextRenderer>()->size = vector2(500, 800);
}

Debug::~Debug()
{

}