#pragma once
#include <vector>

using namespace std;

class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Start();
	void Update();
	void OnDestroy();
	void OnDisable();
	void OnEnable();
	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();
public:
	Transform* transform;
	bool isStarted = false;
	bool isEnabled = true;

private:
	vector<Component*> componentList;
	vector<Component*>::iterator componentIter;



public:
	template<typename T>
	T* GetComponent()
	{
		vector<Component*>::iterator iter;
		for (iter = componentList.begin(); iter < componentList.end(); iter++)
		{
			if (typeid(T).name() == typeid(**iter).name())
				return (T*)*iter;
		}
		return nullptr;
	}
	template<typename T>
	void AddComponent()
	{
		T* newComponent = new T(transform);
		componentList.push_back(newComponent);
	}
};
