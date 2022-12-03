#include "stdafx.h"

Camera* Camera::main = nullptr;
Camera::Camera() : Component()
{
	if (main == nullptr)
	{
		main = this;
	}
}
Camera::Camera(Transform* t) : Component(t)
{
	if (main == nullptr)
	{
		main = this;
	}
}

Camera::~Camera()
{
}

vector2 Camera::ScreenToWorldPoint(vector2 p)
{
	POINT center = { Screen::width / 2 - transform->position.x, Screen::height / 2 -transform->position.y} ;
	ScreenToClient(Input::hWnd, &center);
	vector2 diff = vector2(center.x, center.y) - vector2(center.x, center.y) * orthoScale;
	vector2 point = diff + p*orthoScale - vector2(center.x, center.y);
	return point;
	//수정 작업 필요
}