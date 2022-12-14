#include "stdafx.h"

LineCollider::LineCollider() :Collider()
{

}

LineCollider::LineCollider(GameObject* t) :Collider(t)
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
	result.other = other;
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
	result.other = other;

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
	 result.other = other;

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

bool LineCollider::InBound(vector2 v)
{
	vector2 center = transform->position;
	float range = radius * (transform->scale.x + transform->scale.y) / 2;
	return vector2::Distance(center, v) <= range;
}

vector2 LineCollider::GetNormalVector(vector2 v)
{
	return vector2::Normalize(v - transform->position);
}