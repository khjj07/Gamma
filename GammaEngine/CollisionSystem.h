#pragma once


enum CollisionState //�ݸ��� ���� �����ϴ� ������
{
	Enter, //�� �浹�ߴ�. 
	Exit, //�� �浹 ���¿��� �����. 
	Stay, //�浹 ���°� �����ǰ� �ִ�.
	Not //�浹���� �ʰ� �ִ�.
};

struct CollisionResponse
{
	CollisionState state;  //�浹 ���� ��Ÿ���� ��ü.
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
