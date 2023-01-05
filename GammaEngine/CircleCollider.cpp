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

	if (other->transform->GetWorldRotation() == 0)
	{
		check = Circle_to_AABB(this, other);
	}
	else
	{
		check = Circle_to_OBB(other, this);
	}

	DecideCollisionState(result, collided, check);

	return result;
}


CollisionResponse GammaEngine::CircleCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	bool check = Circle_to_Circle(this,other);

	result.other = this;

	DecideCollisionState(result, collided, check);

	return result;
}

CollisionResponse GammaEngine::CircleCollider::Check(LineCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;

	bool check = GetIntersectPoint(other->startPoint, other->endPoint, transform->GetWorldPosition(), radius);
	result.other = this;

	DecideCollisionState(result, collided, check);

	return result;
}

bool GammaEngine::CircleCollider::InBound(vector2 v)
{
	vector2 center = transform->GetWorldPosition();
	vector2 scale = transform->GetWorldScale();
	float range = radius*(scale.x+ scale.y)/2;
	return vector2::Distance(center, v) <= range;
}

 vector2 GammaEngine::CircleCollider::GetNormalVector(vector2 v)
{
	 return vector2::Normalize(v - transform->GetWorldPosition());
}