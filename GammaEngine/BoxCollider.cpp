#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::BoxCollider::BoxCollider(GameObject* t) :Collider(t)
{
	debug = new Material(vector4(0,1,0,1));
}

GammaEngine::BoxCollider::~BoxCollider()
{

}

void GammaEngine::BoxCollider::SetBounds(vector2 v)
{
	bounds = v;
}

CollisionResponse GammaEngine::BoxCollider::Collide(Collider* other, bool collided)
{
	CollisionResponse result;
	vector<vector2> polytope;

	ResetPoints();
	bool detect = bounds.Length() != 0 && GJK(this, other, polytope);
	result.other = other;

	if (detect)
	{
 		EPA(this, other, polytope, result.normal, result.distance,result.contactPoint);
	}
	DecideCollisionState(result,collided, detect);
	return result;
}


vector<vector2> GammaEngine::BoxCollider::ComputePoints()
{
	if (simplex.size() != 4)
	{
		vector2 position = transform->position;
		vector2 scale = transform->scale;

		float theta = transform->rotation / 180 * PI;
		Matrix3x3 worldMatrix = transform->GetWorldMatrix();
		vector2 leftUp = (worldMatrix*vector2(-bounds.x/2,-bounds.y / 2).ToMatrix3x1()).tovector2();
		vector2 leftDown = (worldMatrix * vector2(-bounds.x / 2, bounds.y / 2).ToMatrix3x1()).tovector2();
		vector2 rightUp = (worldMatrix * vector2(bounds.x / 2, -bounds.y / 2).ToMatrix3x1()).tovector2();
		vector2 rightDown = (worldMatrix * vector2(bounds.x / 2, bounds.y / 2).ToMatrix3x1()).tovector2();
		simplex.push_back(leftUp);
		simplex.push_back(leftDown);
		simplex.push_back(rightUp);
		simplex.push_back(rightDown);
		return simplex;
	}
	else
	{
		return simplex;
	}
}

void GammaEngine::BoxCollider::ResetPoints()
{
	simplex.clear();
}

vector2 GammaEngine::BoxCollider::FarthestPoint(vector2 v)
{
	return Collider::FarthestPoint(ComputePoints(), v);
}

bool GammaEngine::BoxCollider::InBound(vector2 v)
{
	return GJK(this, v);
}
