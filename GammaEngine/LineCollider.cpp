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

vector2 GammaEngine::LineCollider::FarthestPoint(vector2 v)
{
	vector<vector2> simplex;
	simplex.push_back(startPoint);
	simplex.push_back(endPoint);
	return Collider::FarthestPoint(simplex, v);
}