#pragma once
class Transform;
class Collider;
struct CollisionResponse;
class Component abstract
{
public:
	Component();
	Component(Transform*);
	~Component();
	virtual void Start();
	virtual void Update();
	virtual void OnDestroy();
	virtual void OnDisable();
	virtual void OnEnable();
	virtual void Render();
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();
	Transform* transform;
private:

};

