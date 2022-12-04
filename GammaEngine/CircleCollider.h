#pragma once
class Collider;
class Transform;
class BoxCollider;
struct CollisionResponse;
class CircleCollider :public Collider
{
public:
	CircleCollider();
	CircleCollider(Transform*);
	~CircleCollider();
public:
	virtual bool InBound(vector2);
	virtual CollisionResponse Collide(Collider*, bool);
	virtual vector2 GetNormalVector(vector2);
	CollisionResponse Check(BoxCollider* other, bool collided);
	CollisionResponse Check(CircleCollider* other, bool collided);
public:
	float radius;
private:

};

