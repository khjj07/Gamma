#include "GammaEngine.h"
#include "CircleScript.h"
using namespace GammaEngine;

CircleScript::CircleScript(GameObject* t) :Component(t)
{

}

CircleScript::~CircleScript()
{

}

void CircleScript::Start()
{

}

void CircleScript::Update()
{

}

void CircleScript::OnCollisionStay(CollisionResponse response)
{

}

void CircleScript::OnCollisionExit(CollisionResponse response)
{
	GetComponent<EllipseRenderer>()->SetPen(vector4(0, 0, 0, 1));
}