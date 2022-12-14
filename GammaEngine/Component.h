#pragma once

class GameObject;
class Transform;
struct CollisionResponse;

class Component abstract
{
public:
	Component();
	Component(GameObject* g);
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

public:
	template<typename T>
	T* GetComponent();
	template<typename T>
	void AddComponent();

public:
	GameObject* gameObject;
	Transform* transform;
};

template<typename T>
T* Component::GetComponent()
{
	return gameObject->GetComponent<T>();
}

template<typename T>
void Component::AddComponent()
{
	gameObject->AddComponent<T>();
}
