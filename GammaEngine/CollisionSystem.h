#pragma once
namespace GammaEngine
{
	class Collider;

	/// <summary>
	/// 콜리전의 현재 상태를 구분하는 enum 타입
	/// </summary>
	enum class CollisionState
	{
		Enter,
		Exit,
		Stay,
		Not
	};

	/// <summary>
	/// 콜리전 결과를 반환을 위한 구조체
	/// </summary>
	struct GammaEngineAPI CollisionResponse
	{
		CollisionResponse() : state(CollisionState::Not), other(nullptr){}
		CollisionState state; //상태
		Collider* other; //다른 충돌체
		vector2 normal; //법선벡터
		vector2 position; //충돌 지점
		float distance; //침투 거리
	};

	/// <summary>
	/// 이전 프레임에서의 충돌관계를 저장하는 구조체
	/// </summary>
	struct GammaEngineAPI Collided
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
	class GammaEngineAPI CollisionSystem : public Singleton<CollisionSystem>
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
}
