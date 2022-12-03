#include "stdafx.h"
bool Collider::AABB_to_AABB(rect2D a, rect2D b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
	return true;
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
