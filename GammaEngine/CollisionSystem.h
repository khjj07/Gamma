#pragma once

class Collider;

/// <summary>
/// 콜리전의 현재 상태를 구분하는 enum 타입
/// </summary>
enum CollisionState
{
	Enter, 
	Exit, 
	Stay,
	Not
};

/// <summary>
/// 콜리전 결과를 반환을 위한 구조체
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
/// 이전 프레임에서의 충돌관계를 저장하는 구조체
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
/// 콜리전을 관리하는 class
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
