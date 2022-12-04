#pragma once


enum CollisionState //콜리젼 상태 정의하는 열거형
{
	Enter, //막 충돌했다. 
	Exit, //막 충돌 상태에서 벗어났다. 
	Stay, //충돌 상태가 유지되고 있다.
	Not //충돌하지 않고 있다.
};

struct CollisionResponse
{
	CollisionState state;  //충돌 상태 나타내는 객체.
	Collider* other;
	vector2 normal;
};
struct Collided
{
	Collider* self;
	vector<Collider*>list;
	Collided(Collider* s)
	{
		self = s;
	}
};

class CollisionSystem : public Singleton<CollisionSystem>
{
public:
	CollisionSystem();
	~CollisionSystem();
	void Frame();
public:
	vector<Collider*> colliderList;
	vector<Collided> collidedList;
private:

};
