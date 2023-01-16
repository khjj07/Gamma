#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Rigidbody::Rigidbody(GameObject* t) :Component(t), 
mass(1), velocity(vector2()), 
drag(0.1), momentOfInertia(10), restitution(1),
angularDrag(0.01), angularVelocity(vector2()),torque(vector2()),
staticFriction(1), dynamicFriction(1),
useGravity(false), gravity(vector2::Down * 10)
{

}

GammaEngine::Rigidbody::~Rigidbody()
{

}


void GammaEngine::Rigidbody::Update()
{
	transform->position = transform->position + velocity * Time::deltaTime;
	transform->rotation = acos(vector2::Dot(orient,vector2::Right));

	velocity += acceleration * Time::deltaTime;

	angularAcceleration = torque / momentOfInertia;
	orient = orient + 0.5 * angularVelocity * Time::deltaTime;
	angularVelocity += angularAcceleration * Time::deltaTime;
	orient = orient + 0.5 * angularVelocity * Time::deltaTime;


	if (useGravity)
	{
		velocity = velocity + gravity;
		
	}

	velocity = velocity - velocity * drag;
	torque = torque - torque * angularDrag;
	acceleration = vector2();
	angularAcceleration = vector2();

}

void GammaEngine::Rigidbody::ApplyForce(vector2 force)
{
	acceleration= (1/mass) * force;
}

void GammaEngine::Rigidbody::OnCollisionEnter(CollisionResponse response)
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

void GammaEngine::Rigidbody::OnCollisionStay(CollisionResponse response)
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
	
	// Apply 
	A->velocity -= (1 / A->mass) * frictionImpulse;

	//vector2 momentArmA = res.contactPoint - A->transform->position;
	//vector2 parallelComponentA = momentArmA * (vector2::Dot(frictionImpulse, momentArmA) / vector2::Dot(momentArmA, momentArmA));
	//vector2	angularForceA = frictionImpulse - parallelComponentA;
	//A->torque = angularForceA * momentArmA.Length();
	
	B->velocity += (1 / B->mass) * frictionImpulse;
	//vector2 momentArmB = res.contactPoint - B->transform->position;
	//vector2 parallelComponentB = momentArmB * (vector2::Dot(frictionImpulse, momentArmB) / vector2::Dot(momentArmB, momentArmB));
	//vector2	angularForceB = frictionImpulse - parallelComponentB;
	//B->torque = angularForceB * momentArmB.Length();

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

	// Apply 
	A->velocity -= (1 / A->mass) * frictionImpulse;

	vector2 momentArm =  res.contactPoint-A->transform->position;
	vector2 parallelComponent = momentArm * (vector2::Dot(frictionImpulse, momentArm) / vector2::Dot(momentArm, momentArm));
	vector2	angularForce = frictionImpulse - parallelComponent;
	A->torque = angularForce * momentArm.Length();


	return frictionImpulse;
}

void GammaEngine::Rigidbody::PositionalCorrection(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	const float percent = 0.2;
	const float slop = 0.01;
	vector2 correction = (max(res.distance - slop, 0.0f) / (1 / A->mass + 1 / B->mass)) * percent * res.normal;
	A->transform->position -= (1 / A->mass) * correction;
	B->transform->position += (1 / B->mass) * correction;
}

void GammaEngine::Rigidbody::PositionalCorrection(Rigidbody* A, CollisionResponse res)
{
	const float percent = 0.2;
	const float slop = 0.01;
	vector2 correction = (max(res.distance - slop, 0.0f) / (1 / A->mass )) * percent * res.normal;
	A->transform->position -= (1 / A->mass) * correction;
}
