#pragma once
class Collider;
class Transform;
class CircleCollider;
struct CollisionResponse;
class BoxCollider :public Collider
{
public:
	BoxCollider();
	BoxCollider(GameObject*);
	~BoxCollider();
public:
	virtual bool InBound(vector2);
	virtual CollisionResponse Collide(Collider*, bool);
	virtual vector2 GetNormalVector(vector2);
	CollisionResponse Check(BoxCollider* other, bool collided);
	CollisionResponse Check(CircleCollider* other, bool collided);
public:
	vector2 bounds;
private:

};

