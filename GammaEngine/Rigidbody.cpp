#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Rigidbody::Rigidbody(GameObject* t) :Component(t), 
mass(1), velocity(vector2()), 
drag(0.1), momentOfInertia(10), restitution(0.01),
angularDrag(0.01), angularVelocity(vector2()),torque(vector2()),
staticFriction(0.2), dynamicFriction(0.01),
useGravity(false), gravity(vector2::Down * 10)
{

}

GammaEngine::Rigidbody::~Rigidbody()
{

}


void GammaEngine::Rigidbody::Update()
{
	transform->position = transform->position + velocity * Time::deltaTime;

	if (useGravity)
	{
		velocity = velocity + gravity;
	}

	velocity = velocity - velocity * drag;
}

void GammaEngine::Rigidbody::ApplyForce(vector2 force)
{
	velocity =velocity+ force;
}

void GammaEngine::Rigidbody::OnCollisionEnter(CollisionResponse response)
{
	if (!response.isKinematic)
	{
		Rigidbody* otherRig = response.other->GetComponent<Rigidbody>();
		vector2 impulse;
		if (otherRig)
		{
			impulse = ResolveCollision(this, otherRig, response);
			PositionalCorrection(this, otherRig, response);
		}
		else
		{
			impulse = ResolveCollision(this, response);
			PositionalCorrection(this, response);
		}
	}
}

void GammaEngine::Rigidbody::OnCollisionStay(CollisionResponse response)
{
	if (!response.isKinematic)
	{
		Rigidbody* otherRig = response.other->GetComponent<Rigidbody>();
		vector2 impulse;
		if (otherRig)
		{
			impulse = ResolveCollision(this, otherRig, response);
			PositionalCorrection(this, otherRig, response);
		}
		else
		{
			impulse = ResolveCollision(this, response);
			PositionalCorrection(this, response);
		}
	}
}

void GammaEngine::Rigidbody::OnCollisionExit(CollisionResponse response)
{

}

vector2 GammaEngine::Rigidbody::ResolveCollision(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	vector2 rv = B->velocity - A->velocity;
	
	vector2 tangent =vector2::Normalize( rv - vector2::Dot(rv, res.normal) * res.normal);

	float velAlongNormal = vector2::Dot(rv, res.normal);
	float jt = -vector2::Dot(rv, res.normal);
	jt = jt / (1 / A->mass + 1 / B->mass);

	float mu = pow(A->staticFriction, 2) + pow(B->staticFriction, 2);

	float e = min(A->restitution, B->restitution);

	float j = -(1 + e) * velAlongNormal;
	vector2 frictionImpulse;
	if (abs(jt) < j * mu)
		frictionImpulse = jt * res.normal;
	else
	{
		float dynamicFriction = pow(A->dynamicFriction, 2) + pow(B->dynamicFriction, 2);
		frictionImpulse = -j * res.normal * dynamicFriction;
	}

	A->velocity -= (1 / A->mass) * frictionImpulse;
	B->velocity += (1 / B->mass) * frictionImpulse;

	return frictionImpulse;
}

vector2 GammaEngine::Rigidbody::ResolveCollision(Rigidbody* A, CollisionResponse res)
{
	vector2 rv = - A->velocity;

	vector2 tangent = vector2::Normalize(rv - vector2::Dot(rv, res.normal) * res.normal);

	float velAlongNormal = vector2::Dot(rv, res.normal);

	float jt = -vector2::Dot(rv, res.normal);
	jt = jt / (1 / A->mass);

	float mu = pow(A->staticFriction, 2);

	float e = A->restitution;

	float j = -(1 + e) * velAlongNormal;
	vector2 frictionImpulse; 
	
	if (abs(jt) < j * mu)
		frictionImpulse = jt * res.normal;
	else
	{
		float dynamicFriction = pow(A->dynamicFriction, 2);
		frictionImpulse = -j * res.normal * dynamicFriction;
	}


	A->velocity -= (1 / A->mass) * frictionImpulse;
	return frictionImpulse;
}

void GammaEngine::Rigidbody::PositionalCorrection(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	const float percent = 0.3;
	const float slop = 0.01;
	vector2 correction = (max(res.distance - slop, 0.1f) / (1 / A->mass + 1 / B->mass)) * percent * res.normal;
	
	if (A->mass <= B->mass)
	{
		A->transform->position = A->transform->position - correction;
	}
	if (A->mass >= B->mass)
	{
		B->transform->position = B->transform->position + correction;
	}

}

void GammaEngine::Rigidbody::PositionalCorrection(Rigidbody* A, CollisionResponse res)
{
	const float percent = 0.3;
	const float slop = 0.01;
	vector2 correction = (max(res.distance - slop, 0.1f) / (1 / A->mass )) * percent * res.normal;
	A->transform->position -= (1 / A->mass) * correction;
}
