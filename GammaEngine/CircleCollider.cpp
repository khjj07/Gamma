#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::CircleCollider::CircleCollider(GameObject* t) :Collider(t)
{

}

GammaEngine::CircleCollider::~CircleCollider()
{

}

GammaEngine::CollisionResponse CircleCollider::Collide(Collider* other, bool collided)
{
	return other->Check(this, collided);
}

GammaEngine::CollisionResponse CircleCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	result.other = this;
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
		result.state = CollisionState::Enter;
	}
	else if (collided && check)
	{
		result.state = CollisionState::Stay;
	}
	else if (!collided && !check)
	{
		result.state = CollisionState::Not;
	}
	else if (collided && !check)
	{
		result.state = CollisionState::Exit;
	}

	return result;
}


CollisionResponse GammaEngine::CircleCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;

	vector2 centerA = transform->position;
	float rangeA = (transform->scale.x + transform->scale.y) / 2 * radius;

	vector2 centerB = other->transform->position;
	float rangeB = (other->transform->scale.x + other->transform->scale.y) / 2 * other->radius;

	bool check = Circle_to_Circle(centerA, rangeA, centerB, rangeB);

	result.other = this;

	if (!collided && check)
	{
		result.state = CollisionState::Enter;
	}
	else if (collided && check)
	{
		result.state = CollisionState::Stay;
	}
	else if (!collided && !check)
	{
		result.state = CollisionState::Not;
	}
	else if (collided && !check)
	{
		result.state = CollisionState::Exit;
	}

	return result;
}

CollisionResponse GammaEngine::CircleCollider::Check(LineCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;

	bool check = GetIntersectPoint(other->startPoint, other->endPoint, transform->position, radius);
	result.other = this;

	if (!collided && check)
	{
		result.state = CollisionState::Enter;
	}
	else if (collided && check)
	{
		result.state = CollisionState::Stay;
	}
	else if (!collided && !check)
	{
		result.state = CollisionState::Not;
	}
	else if (collided && !check)
	{
		result.state = CollisionState::Exit;
	}

	return result;
}

bool GammaEngine::CircleCollider::InBound(vector2 v)
{
	vector2 center = transform->position;
	float range = radius*(transform->scale.x+ transform->scale.y)/2;
	return vector2::Distance(center, v) <= range;
}

 vector2 GammaEngine::CircleCollider::GetNormalVector(vector2 v)
{
	 return vector2::Normalize(v - transform->position);
}