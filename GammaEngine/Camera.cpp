#include "stdafx.h"

using namespace GammaEngine;

Camera* Camera::main = nullptr;
GammaEngine::Camera::Camera(GameObject* t) : Component(t)
{
	if (main == nullptr)
	{
		main = this;
	}
}

GammaEngine::Camera::~Camera()
{
}

vector2 GammaEngine::Camera::ScreenToWorldPoint(vector2 p)
{
	POINT center = { Screen::width / 2 - transform->position.x, Screen::height / 2 -transform->position.y} ;
	ScreenToClient(Input::hWnd, &center);
	vector2 diff = vector2(center.x, center.y) - vector2(center.x, center.y) * orthoScale;
	vector2 point = diff + p*orthoScale - vector2(center.x, center.y);
	return point;
}

vector2 GammaEngine::Camera::WorldToScreenPoint(vector2 p)
{
	POINT center = { Screen::width / 2 - transform->position.x, Screen::height / 2 - transform->position.y };
	ScreenToClient(Input::hWnd, &center);
	vector2 diff = vector2(center.x, center.y) - vector2(center.x, center.y) * orthoScale;
	vector2 point = diff + p * orthoScale - vector2(center.x, center.y);
	return point;
}

vector2 GammaEngine::Camera::ScreenToWorldScale(vector2 s)
{
	return s * orthoScale;
}