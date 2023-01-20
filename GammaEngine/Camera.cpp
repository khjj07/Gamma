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
	vector2 center = vector2(Screen::width / 2, Screen::height / 2);
	vector2 size = vector2(1 / Camera::main->orthoScale, 1 / Camera::main->orthoScale);

	Matrix3x1 result = Matrix3x3::Translation(transform->position.x, transform->position.y) * Matrix3x3::Scale(orthoScale,orthoScale) * Matrix3x3::Translation(-center.x, -center.y) * p.ToMatrix3x1();


	return result.tovector2();
}

vector2 GammaEngine::Camera::WorldToScreenPoint(vector2 p)
{
	POINT point = { p.x, p.y };
	vector2 v = vector2(point.x, point.y);
	Matrix1x3 result = v.ToMatrix1x3() * Projection();
	return result.tovector2();
}

vector2 GammaEngine::Camera::ScreenToWorldScale(vector2 s)
{
	return s * orthoScale;
}

Matrix3x3 GammaEngine::Camera::Projection()
{
	vector2 center = vector2(Screen::width / 2, Screen::height / 2);
	vector2 size =vector2(1 / Camera::main->orthoScale , 1 / Camera::main->orthoScale);
	return Matrix3x3::Translation(center.x, center.y) * Matrix3x3::Scale(size.x, size.y)* Matrix3x3::Translation(-transform->position.x, -transform->position.y);
}