#pragma once

class Collider;

/// <summary>
/// �ݸ����� ���� ���¸� �����ϴ� enum Ÿ��
/// </summary>
enum CollisionState
{
	Enter, 
	Exit, 
	Stay,
	Not
};

/// <summary>
/// �ݸ��� ����� ��ȯ�� ���� ����ü
/// </summary>
struct CollisionResponse
{
	CollisionState state;
	Collider* other;
	vector2 normal;
	vector2 position;
	float distance;
};

/// <summary>
/// ���� �����ӿ����� �浹���踦 �����ϴ� ����ü
/// </summary>
struct Collided
{
	Collider* self;
	vector<Collider*>list;
	Collided(Collider* s)
	{
		self = s;
	}
};

/// <summary>
/// �ݸ����� �����ϴ� class
/// </summary>
class CollisionSystem : public Singleton<CollisionSystem>
{
public:
	CollisionSystem();
	~CollisionSystem();

public:
	void Frame();

public:
	vector<Collider*> colliderList;
	vector<Collided> collidedList;
};
