#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Transform::Transform(GameObject* t):Component(t)
{

}

GammaEngine::Transform::~Transform()
{

}

vector2 GammaEngine::Transform::GetWorldPosition()
{
	if (parent)
	{
		return position+parent->GetWorldPosition();
	}
	else
	{
		return position;
	}
}

Matrix3x3 GammaEngine::Transform::GetWorldMatrix()
{
	Matrix3x3 localMatrix;
	localMatrix = Matrix3x3::Scale(scale.x, scale.y)* Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(position.x,position.y) ;
	
	if (parent)
	{
		return parent->GetWorldMatrix() * localMatrix;
	}
	else
	{
		return localMatrix;
	}
}

vector2 GammaEngine::Transform::GetWorldScale()
{
	if (parent)
	{
		vector2 result;
		vector2 p = parent->GetWorldScale();
		result.x = scale.x * p.x;
		result.y = scale.y * p.y;
		return result;
	}
	else
	{
		return scale;
	}
}

void GammaEngine::Transform::SetWorldPosition(vector2 v)
{
	position = v-parent->GetWorldPosition();
}

void GammaEngine::Transform::SetWorldScale(vector2 v)
{
	vector2 p = parent->GetWorldScale();
	scale.x = v.x / p.x;
	scale.y = v.y / p.y;
}