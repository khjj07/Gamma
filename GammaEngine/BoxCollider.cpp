#include "stdafx.h"

BoxCollider::BoxCollider() :Collider()
{

}
BoxCollider::BoxCollider(Transform* t):Collider(t)
{

}


CollisionResponse BoxCollider::Collide(Collider* other, bool collided)
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


CollisionResponse BoxCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;
	result.other = other;

	bool check;
	if (transform->rotation == 0 && other->transform->rotation==0)
	{
		check = AABB_to_AABB(this, other);
	}
	else
	{
		check = OBB_to_OBB(this,other);
	}
	if (check)
	{
		vector2 contactPoint = GetContactPoint(this, other);
		result.normal = other->GetNormalVector(contactPoint);
		result.position = contactPoint;
		result.distance = vector2::Distance(transform->position, contactPoint);
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



CollisionResponse BoxCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = Not;
	result.other = other;
	bool check;
	if (transform->rotation == 0)
	{

		check = Circle_to_AABB(other, this);
	}
	else
	{

		check = Circle_to_OBB(this, other);
		
	}
	if (check)
	{
		vector2 contactPoint = GetContactPoint(this, other);
		result.normal = other->GetNormalVector(contactPoint);
		result.position = contactPoint;
		result.distance = vector2::Distance(transform->position, contactPoint);

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

bool BoxCollider::InBound(vector2 v)
{
	if (transform->rotation == 0)
	{
		rect2D rect;
		rect.min.x = -bounds.x / 2 * transform->scale.x + transform->position.x;
		rect.min.y = -bounds.y / 2 * transform->scale.y + transform->position.y;
		rect.max.x = bounds.x / 2 * transform->scale.x + transform->position.x;
		rect.max.y = bounds.y / 2 * transform->scale.y + transform->position.y;
		return (rect.min.x <= v.x && rect.min.y <= v.y && rect.max.x >= v.x && rect.max.y >= v.y);
	}
	else
	{
		float distance = vector2::Distance(transform->position,v);
		vector2 diffrence = v-transform->position;
		float thetaA = transform->rotation/180*PI;
		vector2 upA = vector2(-sin(thetaA), cos(thetaA));
		vector2 rightA = vector2(cos(thetaA), sin(thetaA));
		if (abs(vector2::Dot(upA, diffrence)) <= bounds.y/2 * transform->scale.y && abs(vector2::Dot(rightA, diffrence)) <= bounds.x/2 * transform->scale.x)
		{
			return true;
		}
		return false;
	}

}

vector2 BoxCollider::GetNormalVector(vector2 v)
{
	v = v - transform->position;
	float thetaA = transform->rotation / 180 * PI;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA));
	vector2 rightA = vector2(cos(thetaA), sin(thetaA));

	vector2 rightUp = upA * bounds.y / 2 * transform->scale.y + rightA * bounds.x / 2 * transform->scale.x;
	vector2 rightDown = -upA * bounds.y / 2 * transform->scale.y + rightA * bounds.x / 2 * transform->scale.x;
	vector2 leftDown = -upA * bounds.y / 2 * transform->scale.y - rightA * bounds.x / 2 * transform->scale.x;
	vector2 leftUp = upA * bounds.y / 2 * transform->scale.y - rightA * bounds.x / 2 * transform->scale.x;


	if (abs(vector2::Dot(upA, v))/ bounds.y / 2 * transform->scale.y < abs(vector2::Dot(rightA, v)/ bounds.x / 2 * transform->scale.x))
	{
		if (vector2::Dot(upA, v) > 0)
		{
			return rightA;

		}
		else
		{
			return -rightA;
		}
		
	}
	else
	{
		if (vector2::Dot(rightA, v) > 0)
		{
			return upA;
		}
		else
		{
			return -upA;
		}
	}
	/*
	if(vector2::Dot(upA,v) < vector2::Dot(upA, rightDown) && vector2::Dot(upA, v) < vector2::Dot(upA, leftDown))
	{
		return -upA;
	}

	if (vector2::Dot(upA, v) < vector2::Dot(upA, rightUp) && vector2::Dot(upA, v) < vector2::Dot(upA, leftUp))
	{
		return upA;
	}

	if (vector2::Dot(rightA, v) < vector2::Dot(rightA, leftUp) && vector2::Dot(rightA, v) < vector2::Dot(rightA, leftDown))
	{
		return -rightA;
	}

	if (vector2::Dot(rightA, v) < vector2::Dot(rightA, rightUp) && vector2::Dot(rightA, v) < vector2::Dot(rightA, rightDown))
	{
		return rightA;
	}
	*/

	
}