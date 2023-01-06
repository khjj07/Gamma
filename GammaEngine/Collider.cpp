#include "stdafx.h"
using namespace GammaEngine;

void GammaEngine::Collider::DecideCollisionState(CollisionResponse& result, bool collided, bool check)
{
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

}

bool GammaEngine::Collider::GetIntersectPoint(vector2 AP1, vector2 AP2,
	vector2 BP1, vector2 BP2, vector2& IP)
{
	double t;
	double s;
	double under = (BP2.y - BP1.y) * (AP2.x - AP1.x) - (BP2.x - BP1.x) * (AP2.y - AP1.y);
	if (under == 0) return false;

	double _t = (BP2.x - BP1.x) * (AP1.y - BP1.y) - (BP2.y - BP1.y) * (AP1.x - BP1.x);
	double _s = (AP2.x - AP1.x) * (AP1.y - BP1.y) - (AP2.y - AP1.y) * (AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;

	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	IP.x = AP1.x + t * (double)(AP2.x - AP1.x);
	IP.y = AP1.y + t * (double)(AP2.y - AP1.y);

	return true;
}

bool GammaEngine::Collider::GetIntersectPoint(vector2 AP1, vector2 AP2,vector2 BP1, float r)
{
	float m = (AP2.y - AP1.y) / (AP2.x - AP1.x);
	float c = -m * AP1.x + AP1.y;
	float d = sqrt((m * BP1.x -BP1.y + c) * (m * BP1.x - BP1.y + c) / (m * m) + 1);
	return d<=r;
}

bool GammaEngine::Collider::AABB_to_AABB(BoxCollider* A, BoxCollider* B)
{
	rect2D a, b;
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();

	a.min.x = -A->bounds.x / 2 * aScale.x + aPosition.x;
	a.min.y = -A->bounds.y / 2 * aScale.y + aPosition.y;
	a.max.x = A->bounds.x / 2 * aScale.x + aPosition.x;
	a.max.y = A->bounds.y / 2 * aScale.y + aPosition.y;

	b.min.x = -B->bounds.x / 2 * bScale.x + bPosition.x;
	b.min.y = -B->bounds.y / 2 * bScale.y + bPosition.y;
	b.max.x = B->bounds.x / 2 * bScale.x + bPosition.x;
	b.max.y = B->bounds.y / 2 * bScale.y + bPosition.y;

	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
	return true;
}

bool GammaEngine::Collider::OBB_to_OBB(BoxCollider* A, BoxCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation= A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation= B->transform->GetWorldRotation();

	vector2 diffrence = aPosition - bPosition;
	float thetaA = aRotation / 180 * PI;
	float thetaB = bRotation / 180 * PI;

	vector2 upA = vector2(-sin(thetaA), cos(thetaA));
	vector2 rightA = vector2(cos(thetaA), sin(thetaA));
	vector2 upB = vector2(-sin(thetaB), cos(thetaB));
	vector2 rightB = vector2(cos(thetaB), sin(thetaB));
	
	if (abs(vector2::Dot(diffrence, upA)) > abs(vector2::Dot(upA, upA * A->bounds.y / 2 * aScale.y)) +
		abs(vector2::Dot(upA, rightA * A->bounds.x / 2 * aScale.x)) +
		abs(vector2::Dot(upA, upB * B->bounds.y / 2 * bScale.y)) +
		abs(vector2::Dot(upA, rightB * B->bounds.x / 2 * bScale.x)))
	{
		return false;
	}
	if (abs(vector2::Dot(diffrence, rightA)) > abs(vector2::Dot(rightA, upA * A->bounds.y / 2 * aScale.y)) +
		abs(vector2::Dot(rightA, rightA * A->bounds.x / 2 * aScale.x)) +
		abs(vector2::Dot(rightA, upB * B->bounds.y / 2 * bScale.y)) +
		abs(vector2::Dot(rightA, rightB * B->bounds.x / 2 * bScale.x)))
	{
		return false;
	}
	if (abs(vector2::Dot(diffrence, upB)) > abs(vector2::Dot(upB, upA * A->bounds.y / 2 * aScale.y)) +
		abs(vector2::Dot(upB, rightA * A->bounds.x / 2 * aScale.x)) +
		abs(vector2::Dot(upB, upB * B->bounds.y / 2 * bScale.y)) +
		abs(vector2::Dot(upB, rightB * B->bounds.x / 2 * bScale.x)))
	{
		return false;
	}
	if (abs(vector2::Dot(diffrence, rightB)) > abs(vector2::Dot(rightB, upA * A->bounds.y / 2 * aScale.y)) +
		abs(vector2::Dot(rightB, rightA * A->bounds.x / 2 *aScale.x)) +
		abs(vector2::Dot(rightB, upB * B->bounds.y / 2 * bScale.y)) +
		abs(vector2::Dot(rightB, rightB * B->bounds.x / 2 * bScale.x)))
	{
		return false;
	}
	return true;
}

bool GammaEngine::Collider::LineToOBB(LineCollider* A, BoxCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation = A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation = B->transform->GetWorldRotation();

	float thetaB = bRotation / 180 * PI;
	vector2 upB = vector2(-sin(thetaB), cos(thetaB));
	vector2 rightB = vector2(cos(thetaB), sin(thetaB));

	vector2 leftUpB = bPosition + upB * B->bounds.y / 2 * bScale.y + rightB * -B->bounds.x / 2 * bScale.x;
	vector2 rightUpB = bPosition + upB * B->bounds.y / 2 * bScale.y + rightB * B->bounds.x / 2 * bScale.x;
	vector2 leftDownB = bPosition + upB * -B->bounds.y / 2 * bScale.y + rightB * -B->bounds.x / 2 * bScale.x;
	vector2 rightDownB = bPosition + upB * -B->bounds.y / 2 * bScale.y + rightB * B->bounds.x / 2 * bScale.x;
	vector2 tmp;

	if (GetIntersectPoint(A->startPoint, A->endPoint, leftUpB, rightUpB, tmp))
	{
		return true;
	}
	if (GetIntersectPoint(A->startPoint, A->endPoint, rightUpB, rightDownB, tmp))
	{
		return true;
	}
	if (GetIntersectPoint(A->startPoint, A->endPoint, rightDownB, leftDownB, tmp))
	{
		return true;
	}
	if (GetIntersectPoint(A->startPoint, A->endPoint, leftDownB, leftUpB, tmp))
	{
		return true;
	}

	return false;
}

bool GammaEngine::Collider::Circle_to_AABB(CircleCollider* A, BoxCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation = A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation = B->transform->GetWorldRotation();

	vector2 center = aPosition;
	float range = (aScale.x + aScale.y) / 2 * A->radius;

	rect2D b;
	b.min.x = -B->bounds.x / 2 * bScale.x + bPosition.x;
	b.min.y = -B->bounds.y / 2 * bScale.y + bPosition.y;
	b.max.x = B->bounds.x / 2 * bScale.x + bPosition.x;
	b.max.y = B->bounds.y / 2 * bScale.y + bPosition.y;

	vector2 dot = center+((b.min + b.max) / 2 - center).Normalize()*range;
	if (A->InBound((b.min + b.max) / 2)|| Physics::InBound(b, dot))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GammaEngine::Collider::Circle_to_OBB(BoxCollider* A, CircleCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation = A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation = B->transform->GetWorldRotation();

	float distance = vector2::Distance(aPosition, bPosition);
	vector2 diffrence = aPosition - bPosition;
	vector2 direction = (aPosition - bPosition).Normalize();

	float thetaA = aRotation / 180 * PI;;
	float scaleB = (bScale.x + bScale.y) / 2;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA)).Normalize();
	vector2 rightA = vector2(cos(thetaA), sin(thetaA)).Normalize();

	if(abs(vector2::Dot(upA, diffrence)) <= A->bounds.y / 2 * aScale.y + B->radius* scaleB && abs(vector2::Dot(rightA, diffrence)) <= A->bounds.x / 2 * aScale.x + B->radius * scaleB)
	{
		return true;
	}
	return false;
}

vector2 GammaEngine::Collider::GetContactPoint(BoxCollider* A, CircleCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation = A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation = B->transform->GetWorldRotation();

	float distance = vector2::Distance(aPosition, bPosition);
	vector2 diffrence = aPosition - bPosition;
	vector2 direction = (aPosition - bPosition).Normalize();
	float thetaA = bRotation / 180 * PI;;
	float scaleB = (bScale.x + bScale.y) / 2;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA)).Normalize();
	vector2 rightA = vector2(cos(thetaA), sin(thetaA)).Normalize();
	vector2 point = vector2(vector2::Dot(upA, diffrence) - vector2::Dot(upA, direction * B->radius * scaleB), vector2::Dot(rightA, diffrence) - vector2::Dot(rightA, direction * B->radius * scaleB));
	return point;
}
vector2 GammaEngine::Collider::FarthestPoint(vector<vector2> set, vector2 direction)
{
	vector2 result;
	vector<vector2>::iterator iter;
 	iter = set.begin();
	result = *iter;
	iter++;
	for (; iter < set.end(); iter++)
	{
		if (vector2::Dot(direction, result) > vector2::Dot(direction, *iter))
		{
			result = *iter;
		}
	}
	return result;
}

vector2 GammaEngine::Collider::SupportFunc(vector<vector2> setA, vector<vector2> setB, vector2 direction)
{
	vector2 A = FarthestPoint(setA, direction);
	vector2 B = FarthestPoint(setB, -direction);
	return A - B;
}

bool GammaEngine::Collider::GJK(BoxCollider* A, BoxCollider* B){
	// First point of pts1-pts2
	vector<vector2> pointA;
	A->ComputePoints(pointA);
	vector<vector2> pointB;
	B->ComputePoints(pointB);


	vector2 a = SupportFunc(pointA, pointB, vector2(1, 1));

	// First direction
	vector2 v = -a;

	// Second point
	vector2 b = SupportFunc(pointA, pointB, v);
	if (vector2::Dot(b, v) <= 0) return false; // Second point fails

	// Second direction
	vector2 ab = b-a;
	v = vector2::tripleProduct(ab, -a, ab);

	for (;;) {
		// Third point
		vector2 c = SupportFunc(pointA, pointB, v);
		if (vector2::Dot(c, v) <= 0) return false; // Third point fails

		vector2 c0 = -c;
		vector2 cb = b - c;
		vector2 ca = a - c;

		vector2 cbPerp = vector2::tripleProduct(ca, cb, cb);
		vector2 caPerp = vector2::tripleProduct(cb, ca, ca);

		if (vector2::Dot(caPerp, c0) > 0) {
			b = c;
			v = caPerp;
		}
		else if (vector2::Dot(cbPerp, c0) > 0) {
			a = c;
			v = cbPerp;
		}
		else
		{
			return true;
		}
	}
}


vector2 GammaEngine::Collider::GetContactPoint(BoxCollider* A, BoxCollider* B)
{
	vector2 aScale = A->transform->GetWorldScale();
	vector2 aPosition = A->transform->GetWorldPosition();
	float aRotation = A->transform->GetWorldRotation();
	vector2 bScale = B->transform->GetWorldScale();
	vector2 bPosition = B->transform->GetWorldPosition();
	float bRotation = B->transform->GetWorldRotation();

	float thetaA = aRotation / 180 * PI;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA));
	vector2 rightA = vector2(cos(thetaA), sin(thetaA));
	float thetaB = bRotation / 180 * PI;
	vector2 upB = vector2(-sin(thetaB), cos(thetaB));
	vector2 rightB = vector2(cos(thetaB), sin(thetaB));

	vector2 leftUpA = aPosition + upA * A->bounds.y / 2 * aScale.y + rightA * -A->bounds.x / 2 * aScale.x;
	vector2 rightUpA = aPosition + upA * A->bounds.y / 2 * aScale.y + rightA * A->bounds.x / 2 * aScale.x;
	vector2 leftDownA = aPosition + upA * -A->bounds.y / 2 * aScale.y + rightA * -A->bounds.x / 2 * aScale.x;
	vector2 rightDownA = aPosition + upA * -A->bounds.y / 2 * aScale.y + rightA * A->bounds.x / 2 * aScale.x;

	vector2 leftUpB = bPosition + upB * B->bounds.y / 2 * bScale.y + rightB * -B->bounds.x / 2 * bScale.x;
	vector2 rightUpB = bPosition + upB * B->bounds.y / 2 * bScale.y + rightB * B->bounds.x / 2 * bScale.x;
	vector2 leftDownB = bPosition + upB * -B->bounds.y / 2 * bScale.y + rightB * -B->bounds.x / 2 * bScale.x;
	vector2 rightDownB = bPosition + upB * -B->bounds.y / 2 * bScale.y + rightB * B->bounds.x / 2 * bScale.x;

	vector2 result,tmp;
	int count = 0;
	if (GetIntersectPoint(aPosition, leftUpA, leftUpB, rightUpB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftUpA, rightUpB, rightDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftUpA, rightDownB, leftDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftUpA, leftDownB, leftUpB, tmp))
	{
		return tmp;
	}

	if (GetIntersectPoint(aPosition, rightUpA, leftUpB, rightUpB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightUpA, rightUpB, rightDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightUpA, rightDownB, leftDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightUpA, leftDownB, leftUpB, tmp))
	{
		return tmp;
	}

	if (GetIntersectPoint(aPosition, rightDownA, leftUpB, rightUpB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightDownA, rightUpB, rightDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightDownA, rightDownB, leftDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, rightDownA, leftDownB, leftUpB, tmp))
	{
		return tmp;
	}

	if (GetIntersectPoint(aPosition, leftDownA, leftUpB, rightUpB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftDownA, rightUpB, rightDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftDownA, rightDownB, leftDownB, tmp))
	{
		return tmp;
	}
	if (GetIntersectPoint(aPosition, leftDownA, leftDownB, leftUpB, tmp))
	{
		return tmp;
	}
}

bool GammaEngine::Collider::Circle_to_Circle(CircleCollider* A, CircleCollider* B)
{
	vector2 centerA = A->transform->GetWorldPosition();
	vector2 scaleA = A->transform->GetWorldScale();

	float rangeA = (scaleA.x + scaleA.y) / 2 * A->radius;

	vector2 centerB = B->transform->GetWorldPosition();
	vector2 scaleB = B->transform->GetWorldScale();
	float rangeB = (scaleB.x + scaleB.y) / 2 * B->radius;
	
	return vector2::Distance(centerA, centerB) <= rangeA + rangeB;
}

GammaEngine::Collider::Collider(GameObject* t) : Component(t)
{
	CollisionSystem::Instance()->colliderList.push_back(this);
	CollisionSystem::Instance()->collidedList.push_back(Collided(this));
}

GammaEngine::Collider::~Collider()
{
	CollisionSystem* coll = CollisionSystem::Instance();
	coll->colliderList.erase(remove_if(coll->colliderList.begin(), coll->colliderList.end(), [this](Collider* x) { if (x == this) return true; else return false; }), coll->colliderList.end());
}

bool GammaEngine::Collider::CompareTag(string str)
{
	return this->gameObject->CompareTag(str);
}

bool GammaEngine::Collider::CompareTag(char* str)
{
	return this->gameObject->CompareTag(str);
}

bool GammaEngine::Collider::CompareTags(vector<string> strList)
{
	vector<string>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

bool GammaEngine::Collider::CompareTags(vector<char*> strList)
{
	vector<char*>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

vector2 GammaEngine::Collider::GetNormalVector(vector2 v)
{
	return vector2();
}

bool GammaEngine::Collider::InBound(vector2 v)
{
	return false;	
}