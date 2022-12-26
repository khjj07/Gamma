#pragma once
namespace GammaEngine
{
	class Collider;

	/// <summary>
	/// �ݸ����� ���� ���¸� �����ϴ� enum Ÿ��
	/// </summary>
	enum class CollisionState
	{
		Enter,
		Exit,
		Stay,
		Not
	};

	/// <summary>
	/// �ݸ��� ����� ��ȯ�� ���� ����ü
	/// </summary>
	struct GammaEngineAPI CollisionResponse
	{
		CollisionResponse() : state(CollisionState::Not), other(nullptr){}
		CollisionState state; //����
		Collider* other; //�ٸ� �浹ü
		vector2 normal; //��������
		vector2 position; //�浹 ����
		float distance; //ħ�� �Ÿ�
	};

	/// <summary>
	/// ���� �����ӿ����� �浹���踦 �����ϴ� ����ü
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
	/// �ݸ����� �����ϴ� class
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
