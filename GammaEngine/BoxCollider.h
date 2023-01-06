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
	class CircleCollider;
	struct CollisionResponse;

	/// <summary>
	/// 박스 콜라이더 class
	/// </summary>
	class GammaEngineAPI BoxCollider :public Collider
	{
	public:
		friend class Collider;
		friend class Physics;

	public:
		BoxCollider(GameObject*);
		~BoxCollider();

	public:
		virtual bool InBound(vector2);
		virtual vector2 GetNormalVector(vector2);
		virtual CollisionResponse Collide(Collider*, bool);
		virtual CollisionResponse Check(BoxCollider* other, bool collided);
		virtual CollisionResponse Check(CircleCollider* other, bool collided);
		virtual CollisionResponse Check(LineCollider* other, bool collided);
	
	public:
		void SetBounds(vector2);
		void ComputePoints(vector<vector2>&);
	private:
		vector2 bounds;
	};
}

