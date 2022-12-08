#include "stdafx.h"
#include "BoxScript.h"

BoxScript::BoxScript()
{
}

BoxScript::BoxScript(Transform* t) :Component(t)
{
}

BoxScript::~BoxScript()
{
}

void BoxScript::Start()
{

}

void BoxScript::Update()
{
	transform->position += velocity*Time::deltaTime;
	//velocity += gravity;
    correction = vector2();
}

void BoxScript::OnCollisionEnter(CollisionResponse response)
{
   

}

void BoxScript::OnCollisionStay(CollisionResponse response)
{
    float proj = vector2::Dot(correction, response.normal);
    vector2 comp = response.normal* (response.distance - proj);
    correction = correction + comp;
    transform->position += comp;
    proj = vector2::Dot(velocity, response.normal);
    if (proj < 0)
    {
        velocity = velocity - response.normal * proj;
    }
}


void BoxScript::OnCollisionExit(CollisionResponse response)
{
	
}