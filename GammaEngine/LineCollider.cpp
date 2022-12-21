#include "stdafx.h"
LineCollider::LineCollider(GameObject* t) :Collider(t)
{

}

LineCollider::~LineCollider()
{

}

CollisionResponse LineCollider::Collide(Collider* other, bool collided)
{
	return other->Check(this, collided);
}

CollisionResponse LineCollider::Check(BoxCollider* other, bool collided)
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

CollisionResponse LineCollider::Check(CircleCollider* other, bool collided)
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

CollisionResponse LineCollider::Check(LineCollider* other, bool collided)
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

vector2 LineCollider::GetNormalVector(vector2 v)
{
	return vector2::Normalize(v - transform->position);
}