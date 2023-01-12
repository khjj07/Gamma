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
	bool detect = GJK(this, other, polytope);
	result.other = other;
	vector2 normal;
	float distance;

	if (detect)
	{
 		EPA(this, other, polytope, normal, distance);
		result.normal = normal;
		result.distance = distance;
	}
#if DEBUG
	vector2 position = transform->position;
	this->GetComponent<RectangleRenderer>()->Adjust(position);
	Debug::DrawLine(position, position +result.normal*result.distance,2,debug);
#endif
	DecideCollisionState(result,collided, detect);
	return result;
}


vector<vector2> GammaEngine::BoxCollider::ComputePoints()
{
	if (simplex.size()!=4)
	{
		vector2 position = transform->position;
		vector2 scale = transform->scale;

		float theta = transform->rotation / 180 * PI;
		vector2 up = vector2(-sin(theta), cos(theta));
		vector2 right = vector2(cos(theta), sin(theta));

		simplex.push_back(position + up * bounds.y * scale.y / 2 + right * bounds.x * scale.x / 2);
		simplex.push_back(position + up * bounds.y * scale.y / 2 - right * bounds.x * scale.x / 2);
		simplex.push_back(position - up * bounds.y * scale.y / 2 + right * bounds.x * scale.x / 2);
		simplex.push_back(position - up * bounds.y * scale.y / 2 - right * bounds.x * scale.x / 2);
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
