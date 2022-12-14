#include "stdafx.h"

CircleCollider::CircleCollider() :Collider()
{

}

CircleCollider::CircleCollider(GameObject* t) :Collider(t)
{

}


CollisionResponse CircleCollider::Collide(Collider* other, bool collided)
{
	BoxCollider* boxOther = dynamic_cast<BoxCollider*>(other);
	CircleCollider* circleOther = dynamic_cast<CircleCollider*>(other);
	if (boxOther)
	{
		return Check(boxOther, collided);
	}
	else if (circleOther)
	{
		return Check(circleOther, collided);
	}

}


CollisionResponse CircleCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;
	result.other = other;
	bool check;
	if (other->transform->rotation == 0)
	{
		check = Circle_to_AABB(this, other);
	}
	else
	{
		check = Circle_to_OBB(other, this);
	}

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


CollisionResponse CircleCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;

	vector2 centerA = transform->position;
	float rangeA = (transform->scale.x + transform->scale.y) / 2 * radius;
	vector2 centerB = other->transform->position;
	float rangeB = (other->transform->scale.x + other->transform->scale.y) / 2 * other->radius;
	bool check = Circle_to_Circle(centerA, rangeA, centerB, rangeB);
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



bool CircleCollider::InBound(vector2 v)
{
	vector2 center = transform->position;
	float range = radius*(transform->scale.x+ transform->scale.y)/2;
	return vector2::Distance(center, v) <= range;
}

 vector2 CircleCollider::GetNormalVector(vector2 v)
{
	 return vector2::Normalize(v - transform->position);
}