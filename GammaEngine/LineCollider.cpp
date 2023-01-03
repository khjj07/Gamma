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

CollisionResponse GammaEngine::LineCollider::Check(BoxCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;
	result.other = this;
	bool check;
	
	check = LineToOBB(this,other);
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

CollisionResponse GammaEngine::LineCollider::Check(CircleCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;

	bool check = GetIntersectPoint(startPoint, endPoint, other->transform->position, other->radius);
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

CollisionResponse GammaEngine::LineCollider::Check(LineCollider* other, bool collided)
{
	CollisionResponse result;
	result.state = CollisionState::Not;

	 bool check= GetIntersectPoint(startPoint, endPoint, other->startPoint, other->endPoint, result.position);
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

vector2 GammaEngine::LineCollider::GetNormalVector(vector2 v)
{
	return vector2::Normalize(v - transform->GetWorldPosition());
}