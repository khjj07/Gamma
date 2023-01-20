#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::PolygonCollider::PolygonCollider(GameObject* t) :Collider(t)
{
	debug = new Material(vector4(0, 1, 0, 1));
}

GammaEngine::PolygonCollider::~PolygonCollider()
{

}

void GammaEngine::PolygonCollider::SetPoints(vector<vector2>p)
{
	points = p;
}

CollisionResponse GammaEngine::PolygonCollider::Collide(Collider* other, bool collided)
{
	CollisionResponse result;
	vector<vector2> polytope;

	ResetPoints();
	bool detect = GJK(this, other, polytope);
	result.other = other;
	result.isKinematic = isKinematic || other->isKinematic;
	if (detect)
	{
		EPA(this, other, polytope, result.normal, result.distance, result.contactPoint);
	}
	DecideCollisionState(result, collided, detect);
	return result;
}


vector<vector2> GammaEngine::PolygonCollider::ComputePoints()
{
	if (simplex.size() != points.size())
	{
		vector2 position = transform->position;
		vector2 scale = transform->scale;

		Matrix3x3 worldMatrix = transform->GetWorldMatrix();
		for (int i = 0; i < points.size(); i++)
		{
			vector2 p = (worldMatrix * points[i].ToMatrix3x1()).tovector2();
			simplex.push_back(p);
		}
		return simplex;
	}
	else
	{
		return simplex;
	}
}

void GammaEngine::PolygonCollider::ResetPoints()
{
	simplex.clear();
}

vector2 GammaEngine::PolygonCollider::FarthestPoint(vector2 v)
{
	return Collider::FarthestPoint(ComputePoints(), v);
}

bool GammaEngine::PolygonCollider::InBound(vector2 v)
{
	return GJK(this, v);
}
