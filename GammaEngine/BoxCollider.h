#pragma once
class Collider;
class Transform;
struct CollisionResponse;
class BoxCollider :public Collider
{
public:
	BoxCollider();
	BoxCollider(Transform*);
	~BoxCollider();
public:
	virtual CollisionResponse Collide(Collider*, bool);
	CollisionResponse Check(BoxCollider* other, bool collided);
private:

};

