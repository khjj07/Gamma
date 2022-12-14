#pragma once
class Collider;
class Transform;
class BoxCollider;
struct CollisionResponse;

class LineCollider :public Collider
{
public:
	LineCollider();
	LineCollider(GameObject*);
	~LineCollider();

public:
	virtual bool InBound(vector2);
	virtual CollisionResponse Collide(Collider*, bool);
	virtual vector2 GetNormalVector(vector2);
	virtual CollisionResponse Check(BoxCollider* other, bool collided);
	virtual CollisionResponse Check(CircleCollider* other, bool collided);
	virtual CollisionResponse Check(LineCollider* other, bool collided);

public:
	vector2 startPoint;
	vector2 endPoint;
};

