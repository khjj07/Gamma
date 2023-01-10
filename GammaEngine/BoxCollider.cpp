#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::BoxCollider::BoxCollider(GameObject* t) :Collider(t)
{

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
	
	bool detect = GJK(this, other, polytope);
	result.other = other;
	if (detect)
	{
		EPA(this, other, polytope, result.normal, result.distance);
	}
	DecideCollisionState(result, detect, collided);
	return result;
}


vector<vector2> GammaEngine::BoxCollider::ComputePoints()
{
	vector<vector2> point;
	vector2 position = transform->GetWorldPosition();
	vector2 scale = transform->GetWorldScale();

	float theta = transform->GetWorldRotation() / 180 * PI;
	vector2 up = vector2(-sin(theta), cos(theta));
	vector2 right = vector2(cos(theta), sin(theta));

	point.push_back(position+up * bounds.y * scale.y/2+right* bounds.x * scale.x/2);
	point.push_back(position-up * bounds.y * scale.y/2+right* bounds.x * scale.x/2);
	point.push_back(position+up * bounds.y * scale.y/2-right* bounds.x * scale.x/2);
	point.push_back(position-up * bounds.y * scale.y/2-right* bounds.x * scale.x/2);
	return point;
}

vector2 GammaEngine::BoxCollider::FarthestPoint(vector2 v)
{
	return Collider::FarthestPoint(ComputePoints(), v);
}

bool GammaEngine::BoxCollider::InBound(vector2 v)
{
	return GJK(this, v);
}
