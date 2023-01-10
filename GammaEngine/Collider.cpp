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

vector2 GammaEngine::Collider::FarthestPoint(vector<vector2> set, vector2 direction)
{
	vector2 result;
	vector<vector2>::iterator iter;
 	iter = set.begin();
	result = *iter;
	iter++;
	for (; iter < set.end(); iter++)
	{
		if (vector2::Dot(direction, result) < vector2::Dot(direction, *iter))
		{
			result = *iter;
		}
	}
	return result;
}

vector2 GammaEngine::Collider::Support(Collider* A, Collider* B, vector2 direction)
{
	vector2 fA = A->FarthestPoint(direction);
	vector2 fB = B->FarthestPoint(-direction);
	return fA - fB;
}

vector2 GammaEngine::Collider::Support(Collider* A, vector2 v, vector2 direction)
{
	vector2 fA = A->FarthestPoint(direction);
	return fA - v;
}

bool GammaEngine::Collider::GJK(Collider* A, Collider* B, vector<vector2>& result)
{
	vector2 direction = B->transform->GetWorldPosition() - A->transform->GetWorldPosition();
	vector2 a = Support(A, B, direction);

	vector2 v = -a;

	vector2 b = Support(A, B, v);

	if (vector2::Dot(b, v) <= 0) return false;

	vector2 ab = b-a;
	v = vector2::TripleProduct(ab, -a, ab);

	for (;;) {
		vector2 c = Support(A, B, v);
		if (vector2::Dot(c, v) <= 0) return false;

		vector2 c0 = -c;
		vector2 cb = b - c;
		vector2 ca = a - c;

		vector2 cbPerp = vector2::TripleProduct(ca, cb, cb);
		vector2 caPerp = vector2::TripleProduct(cb, ca, ca);
		
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
			result.push_back(a);
			result.push_back(b);
			result.push_back(c);
			return true;
		}
	}
}

bool GammaEngine::Collider::GJK(Collider* A, vector2 vv)
{
	vector2 direction = A->transform->GetWorldPosition() - vv;
	vector2 a = Support(A, vv, direction);

	vector2 v = -a;

	vector2 b = Support(A, v, v);

	if (vector2::Dot(b, v) <= 0) return false;

	vector2 ab = b - a;
	v = vector2::TripleProduct(ab, -a, ab);

	for (;;) {
		vector2 c = Support(A, v, v);
		if (vector2::Dot(c, v) <= 0) return false;

		vector2 c0 = -c;
		vector2 cb = b - c;
		vector2 ca = a - c;

		vector2 cbPerp = vector2::TripleProduct(ca, cb, cb);
		vector2 caPerp = vector2::TripleProduct(cb, ca, ca);

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

void GammaEngine::Collider::ClosesetEdge(vector<vector2>& polytope, vector2& normal,float& distance)
{
	float npts = polytope.size();
	float dmin = 1000000;
	int N = polytope.size();
	for (int i = 0; i < N; i++)
	{
		vector2 a = polytope[i];
		vector2 b = polytope[(i + 1) % N];
		vector2 l = b - a;
		vector2 n = vector2::Normalize(vector2::TripleProduct(l,a,l));
		float dist = vector2::Dot(n, a);
		if (dist < dmin)
		{
			dmin = dist;
			normal = n;
			distance = dist;
		}
	}
}

void GammaEngine::Collider::EPA(Collider* A, Collider* B, vector<vector2>& polytope, vector2& normal, float& distance)
{
	for (;;) 
	{
		ClosesetEdge(polytope, normal, distance);
		vector2 r = Support(A, B, normal);
		if (abs(vector2::Dot(normal, r) - distance) < 0.01)
		{
			break;
		}
		auto it2 = find(polytope.begin(), polytope.end(), r);
		if(it2 != polytope.end())
		{
			break;
		}
		polytope.push_back(r);
	}
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

 vector2 GammaEngine::Collider::FarthestPoint(vector2 v)
{
	 return vector2();
}

bool GammaEngine::Collider::InBound(vector2 v)
{
	return false;	
}