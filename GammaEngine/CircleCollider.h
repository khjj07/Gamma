#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Collider;
	class Transform;
	class BoxCollider;
	struct CollisionResponse;

	/// <summary>
	/// 원 콜라이더 class
	/// </summary>

	class GammaEngineAPI CircleCollider :public Collider
	{
	public:
		CircleCollider(GameObject*);
		~CircleCollider();

	public:
		virtual bool InBound(vector2);
		virtual CollisionResponse Collide(Collider*, bool);
		virtual vector2 GetNormalVector(vector2);
		virtual CollisionResponse Check(BoxCollider* other, bool collided);
		virtual CollisionResponse Check(CircleCollider* other, bool collided);
		virtual CollisionResponse Check(LineCollider* other, bool collided);

	public:
		float radius;
	};
}


