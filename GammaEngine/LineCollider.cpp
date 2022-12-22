#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::LineCollider::LineCollider(GameObject* t) :Collider(t)
{

}

GammaEngine::LineCollider::~LineCollider()
{

}

CollisionResponse GammaEngine::LineCollider::Collide(Collider* other, bool collided)
{
	return other->Check(this, collided);
}

CollisionResponse GammaEngine::LineCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;
	result.other = this;
	bool check;
	
	check = LineToOBB(this,other);
	if (!collided && check)
	{
		result.state = Enter;
	}
	else if (collided && check)
	{
		result.state = Stay;
	}
	else if (!collided && !check)
	{
		result.state = Not;
	}
	else if (collided && !check)
	{
		result.state = Exit;
	}

	return result;
}

CollisionResponse GammaEngine::LineCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;

	bool check = GetIntersectPoint(startPoint, endPoint, other->transform->position, other->radius);
	result.other = this;

	if (!collided && check)
	{
		result.state = Enter;
	}
	else if (collided && check)
	{
		result.state = Stay;
	}
	else if (!collided && !check)
	{
		result.state = Not;
	}
	else if (collided && !check)
	{
		result.state = Exit;
	}

	return result;
}

CollisionResponse GammaEngine::LineCollider::Check(LineCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;

	 bool check= GetIntersectPoint(startPoint, endPoint, other->startPoint, other->endPoint, result.position);
	 result.other = this;

	 if (!collided && check)
	 {
		 result.state = Enter;
	 }
	 else if (collided && check)
	 {
		 result.state = Stay;
	 }
	 else if (!collided && !check)
	 {
		 result.state = Not;
	 }
	 else if (collided && !check)
	 {
		 result.state = Exit;
	 }

	return result;
}

vector2 GammaEngine::LineCollider::GetNormalVector(vector2 v)
{
	return vector2::Normalize(v - transform->position);
}