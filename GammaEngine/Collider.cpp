#include "stdafx.h"

bool Collider::GetIntersectPoint(vector2 AP1, vector2 AP2,
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

bool Collider::AABB_to_AABB(BoxCollider* A, BoxCollider* B)
{
	rect2D a, b;
	a.min.x = -A->bounds.x / 2 * A->transform->scale.x + A->transform->position.x;
	a.min.y = -A->bounds.y / 2 * A->transform->scale.y + A->transform->position.y;
	a.max.x = A->bounds.x / 2 * A->transform->scale.x + A->transform->position.x;
	a.max.y = A->bounds.y / 2 * A->transform->scale.y + A->transform->position.y;

	b.min.x = -B->bounds.x / 2 * B->transform->scale.x + B->transform->position.x;
	b.min.y = -B->bounds.y / 2 * B->transform->scale.y + B->transform->position.y;
	b.max.x = B->bounds.x / 2 * B->transform->scale.x + B->transform->position.x;
	b.max.y = B->bounds.y / 2 * B->transform->scale.y + B->transform->position.y;

	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
	return true;
}
bool Collider::OBB_to_OBB(BoxCollider* A, BoxCollider* B)
{
	float distance = vector2::Distance(A->transform->position, B->transform->position);
	float thetaA = A->transform->rotation / 180 * PI;
	float thetaB = B->transform->rotation / 180 * PI;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA)).Normalize();
	vector2 upB = vector2(-sin(thetaB), cos(thetaB)).Normalize();
	vector2 rightA = vector2(cos(thetaA), sin(thetaA)).Normalize();
	vector2 rightB = vector2(cos(thetaB), sin(thetaB)).Normalize();

	if (distance > abs(vector2::Dot(upA, upA * A->bounds.y / 2 * A->transform->scale.y)) +
		abs(vector2::Dot(upA, rightA * A->bounds.x / 2 * A->transform->scale.x)) +
		abs(vector2::Dot(upA, upB * B->bounds.y / 2 * B->transform->scale.y)) +
		abs(vector2::Dot(upA, rightB * B->bounds.x / 2 * B->transform->scale.x)))
	{
		return false;
	}
	if (distance > abs(vector2::Dot(rightA, upA * A->bounds.y / 2 * A->transform->scale.y)) +
		abs(vector2::Dot(rightA, rightA * A->bounds.x / 2 * A->transform->scale.x)) +
		abs(vector2::Dot(rightA, upB * B->bounds.y / 2 * B->transform->scale.y)) +
		abs(vector2::Dot(rightA, rightB * B->bounds.x / 2 * B->transform->scale.x)))
	{
		return false;
	}
	if (distance > abs(vector2::Dot(upB, upA * A->bounds.y / 2 * A->transform->scale.y)) +
		abs(vector2::Dot(upB, rightA * A->bounds.x / 2 * A->transform->scale.x)) +
		abs(vector2::Dot(upB, upB * B->bounds.y / 2 * B->transform->scale.y)) +
		abs(vector2::Dot(upB, rightB * B->bounds.x / 2 * B->transform->scale.x)))
	{
		return false;
	}
	if (distance > abs(vector2::Dot(rightB, upA * A->bounds.y / 2 * A->transform->scale.y)) +
		abs(vector2::Dot(rightB, rightA * A->bounds.x / 2 * A->transform->scale.x)) +
		abs(vector2::Dot(rightB, upB * B->bounds.y / 2 * B->transform->scale.y)) +
		abs(vector2::Dot(rightB, rightB * B->bounds.x / 2 * B->transform->scale.x)))
	{
		return false;
	}
	return true;
}

bool Collider::Circle_to_AABB(CircleCollider* A, BoxCollider* B)
{
	vector2 center = A->transform->position;
	float range = (A->transform->scale.x + A->transform->scale.y) / 2 * A->radius;

	rect2D b;
	b.min.x = -B->bounds.x / 2 * B->transform->scale.x + B->transform->position.x;
	b.min.y = -B->bounds.y / 2 * B->transform->scale.y + B->transform->position.y;
	b.max.x = B->bounds.x / 2 * B->transform->scale.x + B->transform->position.x;
	b.max.y = B->bounds.y / 2 * B->transform->scale.y + B->transform->position.y;

	vector2 dot = center+((b.min + b.max) / 2 - center).Normalize()*range;
	if (Physics::InBound(b, dot))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Collider::Circle_to_OBB(BoxCollider* A, CircleCollider* B)
{
	float distance = vector2::Distance(A->transform->position, B->transform->position);
	vector2 diffrence = A->transform->position - B->transform->position;
	vector2 direction = (A->transform->position - B->transform->position).Normalize();
	float thetaA = A->transform->rotation / 180 * PI;;
	float scaleB = (B->transform->scale.x + B->transform->scale.y) / 2;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA)).Normalize();
	vector2 rightA = vector2(cos(thetaA), sin(thetaA)).Normalize();
	if (abs(vector2::Dot(upA, diffrence)- vector2::Dot(upA,direction*B->radius*scaleB)) <= A->bounds.y / 2 * A->transform->scale.y && abs(vector2::Dot(rightA, diffrence) - vector2::Dot(rightA, direction * B->radius * scaleB)) <= A->bounds.x / 2 * A->transform->scale.x)
	{
		return true;
	}
	return false;
}

vector2 Collider::GetContactPoint(BoxCollider* A, CircleCollider* B)
{
	float distance = vector2::Distance(A->transform->position, B->transform->position);
	vector2 diffrence = A->transform->position - B->transform->position;
	vector2 direction = (A->transform->position - B->transform->position).Normalize();
	float thetaA = A->transform->rotation / 180 * PI;;
	float scaleB = (B->transform->scale.x + B->transform->scale.y) / 2;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA)).Normalize();
	vector2 rightA = vector2(cos(thetaA), sin(thetaA)).Normalize();
	vector2 point = vector2(vector2::Dot(upA, diffrence) - vector2::Dot(upA, direction * B->radius * scaleB), vector2::Dot(rightA, diffrence) - vector2::Dot(rightA, direction * B->radius * scaleB));
	return point;
}

vector2 Collider::GetContactPoint(BoxCollider* A, BoxCollider* B)
{

	float thetaA = A->transform->rotation / 180 * PI;
	vector2 upA = vector2(-sin(thetaA), cos(thetaA));
	vector2 rightA = vector2(cos(thetaA), sin(thetaA));
	float thetaB = B->transform->rotation / 180 * PI;
	vector2 upB = vector2(-sin(thetaB), cos(thetaB));
	vector2 rightB = vector2(cos(thetaB), sin(thetaB));

	vector2 leftUpA = A->transform->position + upA * A->bounds.y / 2 * A->transform->scale.y + rightA * -A->bounds.x / 2 * A->transform->scale.x;
	vector2 rightUpA = A->transform->position + upA * A->bounds.y / 2 * A->transform->scale.y + rightA * A->bounds.x / 2 * A->transform->scale.x;
	vector2 leftDownA = A->transform->position + upA * -A->bounds.y / 2 * A->transform->scale.y + rightA * -A->bounds.x / 2 * A->transform->scale.x;
	vector2 rightDownA = A->transform->position + upA * -A->bounds.y / 2 * A->transform->scale.y + rightA * A->bounds.x / 2 * A->transform->scale.x;

	vector2 leftUpB = B->transform->position + upB * B->bounds.y / 2 * B->transform->scale.y + rightB * -B->bounds.x / 2 * B->transform->scale.x;
	vector2 rightUpB = B->transform->position + upB * B->bounds.y / 2 * B->transform->scale.y + rightB * B->bounds.x / 2 * B->transform->scale.x;
	vector2 leftDownB = B->transform->position + upB * -B->bounds.y / 2 * B->transform->scale.y + rightB * -B->bounds.x / 2 * B->transform->scale.x;
	vector2 rightDownB = B->transform->position + upB * -B->bounds.y / 2 * B->transform->scale.y + rightB * B->bounds.x / 2 * B->transform->scale.x;

	vector2 result,tmp;
	int count = 0;
	if (GetIntersectPoint(A->transform->position, B->transform->position, leftUpB, rightUpB, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(A->transform->position, B->transform->position, rightUpB, rightDownB, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(A->transform->position, B->transform->position, rightDownB, leftDownB, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(A->transform->position, B->transform->position, leftDownB, leftUpB, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(B->transform->position, A->transform->position, leftUpA, rightUpA, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(B->transform->position, A->transform->position, rightUpA, rightDownA, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(B->transform->position, A->transform->position, rightDownA, leftDownA, tmp))
	{
		result += tmp;
		count++;
	}
	if (GetIntersectPoint(B->transform->position, A->transform->position, leftDownA, leftUpA, tmp))
	{
		result += tmp;
		count++;
	}
	result = result / count;
	return result;
}

bool Collider::Circle_to_Circle(vector2 centerA, float rangeA, vector2 centerB, float rangeB)
{
	return vector2::Distance(centerA, centerB) <= rangeA + rangeB;
}

Collider::Collider() : Component()
{
	CollisionSystem::Instance()->colliderList.push_back(this);
	CollisionSystem::Instance()->collidedList.push_back(Collided(this));
}

Collider::Collider(Transform* t) : Component(t)
{
	CollisionSystem::Instance()->colliderList.push_back(this);
	CollisionSystem::Instance()->collidedList.push_back(Collided(this));
	gameObject = transform->gameObject;
}


Collider::~Collider()
{
}

bool Collider::CompareTag(string str)
{
	return this->gameObject->CompareTag(str);
}

bool Collider::CompareTag(char* str)
{
	return this->gameObject->CompareTag(str);
}

bool Collider::CompareTags(vector<string> strList)
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

bool Collider::CompareTags(vector<char*> strList)
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

vector2 Collider::GetNormalVector(vector2 v)
{
	return vector2();
}

bool Collider::InBound(vector2 v)
{
	return false;	
}