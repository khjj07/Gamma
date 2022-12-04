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
	void LateUpdate();
	void OnDestroy();
	void OnDisable();
	void OnEnable();
	void OnCollisionEnter(CollisionResponse response);
	void OnCollisionStay(CollisionResponse response);
	void OnCollisionExit(CollisionResponse response);
	bool CompareTag(string);
	bool CompareTag(char*);
	bool CompareTags(vector<string>);
	bool CompareTags(vector<char*>);

public:
	Transform* transform;
	string tag=string("");
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
