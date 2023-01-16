#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// °­Ã¼
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Rigidbody : public Component
	{
	public:
		Rigidbody(GameObject* t);
		~Rigidbody();

	public:
		void ApplyForce(vector2);
		virtual void Update();
		virtual void OnCollisionEnter(CollisionResponse);
		virtual void OnCollisionStay(CollisionResponse);
		virtual void OnCollisionExit(CollisionResponse);

	private:
		static vector2 ResolveCollision(Rigidbody* A, Rigidbody* B, CollisionResponse res);
		static vector2 ResolveCollision(Rigidbody* A, CollisionResponse res);
		static void PositionalCorrection(Rigidbody* A, Rigidbody* B, CollisionResponse res);
		static void PositionalCorrection(Rigidbody* A, CollisionResponse res);

	public:
		float mass;
		float drag;
		float staticFriction;
		float dynamicFriction;
		float angularDrag;
		float restitution;
		vector2 velocity;
		vector2 orient;
		vector2 torque;
		vector2 angularVelocity;
		vector2 gravity;
		float momentOfInertia;
		bool useGravity;

	};
}

