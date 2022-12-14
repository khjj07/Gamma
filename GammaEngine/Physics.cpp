#include "stdafx.h"


Physics::Physics()
{

}

Physics::~Physics()
{

}

bool Physics::InBound(rect2D rect, vector2 v)
{
	return (rect.min.x <= v.x && rect.min.y <= v.y && rect.max.x >= v.x && rect.max.y >= v.y);
}

RaycastResponse  Physics::Raycast(vector2 from, vector2 to, string tag)
{
	CollisionSystem* system = CollisionSystem::Instance();
	RaycastResponse result;
	result.hit = false;
	vector2 v = vector2(to.x - from.x, to.y - from.y);
	int count = abs(v.x) > abs(v.y) ? abs(v.x) : abs(v.y);
	from.x = (float)round(from.x);
	from.y = (float)round(from.y);
	vector2 d = { v.x / count,v.y / count };
	vector<Collider*>::iterator iter;
	vector<Collider*> rayList = system->colliderList;
	sort(rayList.begin(), rayList.end(), [from,v](Collider* a, Collider* b) {
		float objectRangeA, objectRangeB;
		bool OnDirectionA, OnDirectionB;
		bool InRangeA, InRangeB;
		GetRayCondition(from, v, a, objectRangeA, OnDirectionA, InRangeA);
		GetRayCondition(from, v, a, objectRangeB, OnDirectionB, InRangeB); 
		return vector2::Distance(a->transform->position, from)- objectRangeA < vector2::Distance(b->transform->position, from) - objectRangeB;
	});
	for (iter = rayList.begin(); iter < rayList.end(); iter++)
	{
		
		float objectRange;
		bool OnDirection;
		bool InRange;
		
		GetRayCondition(from,v,*iter, objectRange, OnDirection, InRange);
		
		if ((*iter)->gameObject->isEnabled && (*iter)->CompareTag(tag) && OnDirection && InRange)
		{
			for (int k = 0; k < count; k++)
			{
				vector2 check = vector2(from.x + d.x * k, from.y + d.y * k);
				if ((*iter)->InBound(check))
				{
					result.gameObject = (*iter)->gameObject;
					result.collider = (*iter);
					result.fraction = k / count;
					result.normal = (*iter)->GetNormalVector(check);
					result.position = check;
					result.hit = true;
					return result;
				}
			}
		}
	}

	return result;
}

RaycastResponse  Physics::Raycast(vector2 from, vector2 to, vector<string> tags)
{
	CollisionSystem* system = CollisionSystem::Instance();
	RaycastResponse result;
	result.hit = false;
	vector2 v = vector2(to.x - from.x,to.y - from.y);
	int count = abs(v.x) > abs(v.y) ? abs(v.x) : abs(v.y);
	from.x = (float)round(from.x);
	from.y = (float)round(from.y);
	vector2 d = { v.x / count,v.y / count };
	vector<Collider*>::iterator iter;

	vector<Collider*> rayList = system->colliderList;
	sort(rayList.begin(), rayList.end(), [from, v](Collider* a, Collider* b) {
		float objectRangeA, objectRangeB;
		bool OnDirectionA, OnDirectionB;
		bool InRangeA, InRangeB;
		GetRayCondition(from, v, a, objectRangeA, OnDirectionA, InRangeA);
		GetRayCondition(from, v, a, objectRangeB, OnDirectionB, InRangeB);
		return vector2::Distance(a->transform->position, from) - objectRangeA < vector2::Distance(b->transform->position, from) - objectRangeB;
	});

	for (iter = rayList.begin(); iter < rayList.end(); iter++)
	{
		float objectRange;
		bool OnDirection;
		bool InRange;

		GetRayCondition(from, v, *iter, objectRange, OnDirection, InRange);

		if ((*iter)->gameObject->isEnabled && (*iter)->CompareTags(tags) && OnDirection && InRange)
		{
			for (int k = 0; k < count; k++)
			{
				vector2 check = vector2( from.x + d.x * k, from.y + d.y * k );
				if ((*iter)->InBound(check))
				{
					result.gameObject = (*iter)->gameObject;
					result.collider = (*iter);
					result.fraction = k / count;
					result.normal = (*iter)->GetNormalVector(check);
					result.position = check;
					result.hit = true;
					return result;
				}
			}
		}
	}
	
	return result;
}

void Physics::GetRayCondition(vector2 from, vector2 v, Collider* col, float& objectRange, bool& OnDirection, bool& InRange)
{
	Transform* transform = col->transform;
	BoxCollider* box = dynamic_cast<BoxCollider*>(col);
	CircleCollider* circle = dynamic_cast<CircleCollider*>(col);
	if (box)
	{
		vector2 bounds = box->bounds;

		rect2D rect;
		rect.min.x = -bounds.x / 2 * transform->scale.x + transform->position.x;
		rect.min.y = -bounds.y / 2 * transform->scale.y + transform->position.y;
		rect.max.x = bounds.x / 2 * transform->scale.x + transform->position.x;
		rect.max.y = bounds.y / 2 * transform->scale.y + transform->position.y;

		objectRange = vector2::Distance(rect.min, rect.max)* (transform->scale.x + transform->scale.y) / 2;
		OnDirection = vector2::Dot(v, rect.min - from) >= 0 || vector2::Dot(v, rect.max - from) >= 0;
		InRange = v.Length() >= vector2::Distance(transform->position, from) - objectRange;
	}
	else if (circle)
	{
		vector2 direction = (transform->position - from).Normalize();

		objectRange = circle->radius * 2 * (transform->scale.x + transform->scale.y) / 2;
		OnDirection = vector2::Dot(v, transform->position - from - direction * objectRange);
		InRange = v.Length() >= vector2::Distance(transform->position, from) - objectRange;
	}
}
