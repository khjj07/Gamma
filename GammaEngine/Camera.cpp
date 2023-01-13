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
	vector2 position = transform->GetWorldPosition();
	POINT center = { Screen::width / 2 - position.x, Screen::height / 2 - position.y} ;
	ScreenToClient(Input::hWnd, &center);
	vector2 diff = vector2(center.x, center.y) - vector2(center.x, center.y) * orthoScale;
	vector2 point = diff + p*orthoScale - vector2(center.x, center.y);
	return point;
}

vector2 GammaEngine::Camera::WorldToScreenPoint(vector2 p)
{
	vector2 position = transform->GetWorldPosition();
	POINT center = { Screen::width / 2 - position.x, Screen::height / 2 - position.y };
	ScreenToClient(Input::hWnd, &center);
	vector2 diff = vector2(center.x, center.y) - vector2(center.x, center.y) * orthoScale;
	vector2 point = diff + p * orthoScale - vector2(center.x, center.y);
	return point;
}

vector2 GammaEngine::Camera::ScreenToWorldScale(vector2 s)
{
	return s * orthoScale;
}

Matrix3x3 GammaEngine::Camera::Projection()
{
	vector2 center = vector2(Screen::width / 2, Screen::height / 2) - Camera::main->transform->position;
	
	vector2 size =vector2(1 / Camera::main->orthoScale , 1 / Camera::main->orthoScale);
	return Matrix3x3::Translation(center.x, center.y) * Matrix3x3::Scale(size.x, size.y);
}