#pragma once
#include <vector>
#include <functional>
using namespace std;

class GameObject;
class Scene
{
public:
	Scene();
	~Scene();
	void Start();
	void Frame();
	void OnDestroy();
	void OnDisable();
	void OnEnable();
	void Enable();
	void Disable();
	void Add(GameObject*);
	void Remove(GameObject*);
public: 
	template<typename T>
	void Hold()
	{
		holdList.push_back([this]() {
			Add(new T());
			});
	};
public:
	vector<GameObject*> gameObjectList;
	vector<GameObject*>::iterator gameObjectIter;
	vector<function<void()> >holdList;
	vector<function<void()> >::iterator holdIter;
};

