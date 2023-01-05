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

	private:
		vector<vector2> simplex;
		vector2 bounds;
	};
}

