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
	return other->Check(this, collided);
}

CollisionResponse GammaEngine::BoxCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	result.other = this;

	bool check;
// 	if (transform->GetWorldRotation() == 0 && other->transform->GetWorldRotation() == 0)
// 	{
// 		check = AABB_to_AABB(this, other);
// 	}
// 	else
// 	{
// 		check = OBB_to_OBB(this,other);
// 	}
	check = GJK(this, other);

	DecideCollisionState(result, collided, check);

	return result;
}

CollisionResponse GammaEngine::BoxCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	result.other = this;
	bool check;
	if (transform->GetWorldRotation() == 0)
	{
		check = Circle_to_AABB(other, this);
	}
	else
	{
		check = Circle_to_OBB(this, other);
	}
	if (check)
	{
		//gjk
	}

	DecideCollisionState(result, collided, check);

	return result;
}

void GammaEngine::BoxCollider::ComputePoints(vector<vector2>& point)
{
	vector2 position = transform->GetWorldPosition();
	vector2 scale = transform->GetWorldScale();

	float theta = transform->GetWorldRotation() / 180 * PI;
	vector2 up = vector2(-sin(theta), cos(theta));
	vector2 right = vector2(cos(theta), sin(theta));

	point.push_back(position+up * bounds.y * scale.y/2+right* bounds.x * scale.x/2);
	point.push_back(position-up * bounds.y * scale.y/2+right* bounds.x * scale.x/2);
	point.push_back(position+up * bounds.y * scale.y/2-right* bounds.x * scale.x/2);
	point.push_back(position-up * bounds.y * scale.y/2-right* bounds.x * scale.x/2);
}

CollisionResponse GammaEngine::BoxCollider::Check(LineCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	result.other = this;
	bool check;

	check = LineToOBB(other, this);

	DecideCollisionState(result, collided, check);

	return result;
}

bool GammaEngine::BoxCollider::InBound(vector2 v)
{

	vector2 position = transform->GetWorldPosition();
	vector2 scale = transform->GetWorldScale();

	if (transform->GetWorldRotation() == 0)
	{
		rect2D rect;
		rect.min.x = -bounds.x / 2 * scale.x + position.x;
		rect.min.y = -bounds.y / 2 * scale.y + position.y;
		rect.max.x = bounds.x / 2 * scale.x + position.x;
		rect.max.y = bounds.y / 2 * scale.y + position.y;
		return (rect.min.x <= v.x && rect.min.y <= v.y && rect.max.x >= v.x && rect.max.y >= v.y);
	}
	else
	{
		float distance = vector2::Distance(position, v);
		vector2 diffrence = v - position;
		float thetaA = transform->GetWorldRotation() / 180 * PI;
		vector2 upA = vector2(-sin(thetaA), cos(thetaA));
		vector2 rightA = vector2(cos(thetaA), sin(thetaA));
		if (abs(vector2::Dot(upA, diffrence)) <= bounds.y / 2 * scale.y && abs(vector2::Dot(rightA, diffrence)) <= bounds.x / 2 * scale.x)
		{
			return true;
		}
		return false;
	}

}

vector2 GammaEngine::BoxCollider::GetNormalVector(vector2 v)
{
	vector2 scale = transform->GetWorldScale();

	v = v - transform->GetWorldPosition();
	float thetaA = transform->GetWorldRotation() / 180 * PI;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA));
	vector2 rightA = vector2(cos(thetaA), sin(thetaA));

	if (abs(vector2::Dot(upA, v)) / bounds.y / 2 * scale.y < abs(vector2::Dot(rightA, v) / bounds.x / 2 * scale.x))
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
}