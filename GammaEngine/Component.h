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
	virtual void LateUpdate();
	virtual void OnDestroy();
	virtual void OnDisable();
	virtual void OnEnable();
	virtual void Render();
	virtual void OnCollisionEnter(CollisionResponse response);
	virtual void OnCollisionStay(CollisionResponse response);
	virtual void OnCollisionExit(CollisionResponse response);
	Transform* transform;
private:

};

