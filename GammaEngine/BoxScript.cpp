#include "GammaEngine.h"
#include "BoxScript.h"
using namespace GammaEngine;

BoxScript::BoxScript(GameObject* t) :Component(t)
{

}

BoxScript::~BoxScript()
{

}

void BoxScript::Start()
{
	GetComponent<Animation>()->Play(PLAYBACK::LOOP_FORWARD);
}

void BoxScript::Update()
{
	transform->position += velocity * Time::deltaTime;
	//velocity += gravity;
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{
	
}

void BoxScript::OnCollisionStay(CollisionResponse response)
{

}


void BoxScript::OnCollisionExit(CollisionResponse response)
{

}