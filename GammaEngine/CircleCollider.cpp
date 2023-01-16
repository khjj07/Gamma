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
	CollisionResponse result;
	vector<vector2> polytope;

	bool detect = GJK(this, other, polytope);
	result.other = other;
	if (detect)
	{
		EPA(this, other, polytope, result.normal, result.distance, result.contactPoint);
	}
	DecideCollisionState(result, collided, detect);
	return result;
}

bool GammaEngine::CircleCollider::InBound(vector2 v)
{
	vector2 position = transform->GetWorldPosition();
	return vector2::Distance(position, v) <= radius;
}

vector2 GammaEngine::CircleCollider::FarthestPoint(vector2 v)
{
	vector2 position = transform->GetWorldPosition();
	return position+v.Normalize() * radius;
}