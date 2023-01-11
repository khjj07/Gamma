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
	CollisionResponse result;
	vector<vector2> polytope;

	bool detect = GJK(this, other, polytope);
	result.other = other;
	if (detect)
	{
		EPA(this, other, polytope, result.normal, result.distance);
	}
	DecideCollisionState(result, collided, detect);
	return result;
}

vector2 GammaEngine::LineCollider::FarthestPoint(vector2 v)
{
	vector<vector2> simplex;
	simplex.push_back(startPoint);
	simplex.push_back(endPoint);
	return Collider::FarthestPoint(simplex, v);
}