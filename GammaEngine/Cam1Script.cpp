#include "stdafx.h"
#include "Cam1Script.h"

Cam1Script::Cam1Script()
{
}

Cam1Script::Cam1Script(Transform* t) :Component(t)
{
}

Cam1Script::~Cam1Script()
{
}

void Cam1Script::Update()
{
	if(Input::GetKey('A'))
	{
		transform->position.x -= 100 * Time::deltaTime;
	}
	if(Input::GetKey('D'))
	{
		transform->position.x += 100 * Time::deltaTime;
	}
	if(Input::mouseScrollDelta > 0)
	{
		transform->GetComponent<Camera>()->orthoScale += 0.1;
	}
	else if(Input::mouseScrollDelta < 0)
	{
		transform->GetComponent<Camera>()->orthoScale -= 0.1;
	}
}