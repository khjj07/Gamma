#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
class Component;
class GameObject;
class BoxCollider;
class CircleCollider;
class LineCollider;

/// <summary>
/// 콜라이더 추상 class
/// </summary>

	class GammaEngineAPI Collider : public Component
	{
	public:
		Collider(GameObject*);
		~Collider();

	public:
		static bool GetIntersectPoint(vector2 AP1, vector2 AP2, vector2 BP1, vector2 BP2, vector2& IP);
		static bool GetIntersectPoint(vector2 AP1, vector2 AP2, vector2 BP1, float r);
		static bool LineToOBB(LineCollider*, BoxCollider*);
		static bool AABB_to_AABB(BoxCollider*, BoxCollider*);
		static bool OBB_to_OBB(BoxCollider*, BoxCollider*);
		static bool Circle_to_AABB(CircleCollider* A, BoxCollider* B);
		static bool Circle_to_OBB(BoxCollider*, CircleCollider*);
		static bool Circle_to_Circle(vector2 centerA, float rangeA, vector2 centerB, float rangeB);
		static vector2 GetContactPoint(BoxCollider*, CircleCollider*);
		static vector2 GetContactPoint(BoxCollider*, BoxCollider*);

	public:
		bool CompareTag(string str);
		bool CompareTag(char* str);
		bool CompareTags(vector<string> strList);
		bool CompareTags(vector<char*> strList);

	public:
		virtual bool InBound(vector2);
		virtual vector2 GetNormalVector(vector2);
		virtual CollisionResponse Collide(Collider*, bool) = 0;
		virtual CollisionResponse Check(BoxCollider*, bool) = 0;
		virtual CollisionResponse Check(CircleCollider*, bool) = 0;
		virtual CollisionResponse Check(LineCollider*, bool) = 0;
	};


}
