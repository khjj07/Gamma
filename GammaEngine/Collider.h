#pragma once
class Component;
class GameObject;
class Collider : public Component
{
public:
	Collider();
	Collider(Transform*);
	~Collider();
public:
	static bool AABB_to_AABB(rect2D a, rect2D b);
public:
	virtual CollisionResponse Collide(Collider*, bool) = 0;
public:
	vector2 bounds;
	GameObject* gameObject;
private:

};

