#pragma once

class Collider;
class Transform;
class BoxCollider;
struct CollisionResponse;

/// <summary>
/// Line 콜라이더
/// </summary>
class LineCollider :public Collider
{
public:
	LineCollider();
	LineCollider(GameObject*);
	~LineCollider();

public:
	virtual CollisionResponse Collide(Collider*, bool);
	virtual vector2 GetNormalVector(vector2);
	virtual CollisionResponse Check(BoxCollider* other, bool collided);
	virtual CollisionResponse Check(CircleCollider* other, bool collided);
	virtual CollisionResponse Check(LineCollider* other, bool collided);

public:
	vector2 startPoint;
	vector2 endPoint;
};

