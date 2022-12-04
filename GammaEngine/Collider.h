#pragma once
class Component;
class GameObject;
class BoxCollider;
class CircleCollider;
class Collider : public Component
{
public:
	Collider();
	Collider(Transform*);
	~Collider();
public:
	static bool AABB_to_AABB(BoxCollider*, BoxCollider*);
	static bool OBB_to_OBB(BoxCollider*,BoxCollider*);
	static bool Circle_to_AABB(CircleCollider* A, BoxCollider* B);
	static bool Circle_to_OBB(BoxCollider*, CircleCollider*);
	static vector2 GetContactPoint(BoxCollider*, CircleCollider*);
	static bool Circle_to_Circle(vector2 centerA, float rangeA, vector2 centerB, float rangeB);
	bool CompareTag(string str);
	bool CompareTag(char* str);
	bool CompareTags(vector<string> strList);
	bool CompareTags(vector<char*> strList);
public:
	virtual bool InBound(vector2);
	virtual vector2 GetNormalVector(vector2);
	virtual CollisionResponse Collide(Collider*, bool) = 0;
public:
	GameObject* gameObject;
private:

};

