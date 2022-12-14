#pragma once

class GameObject;

/// <summary>
/// ¾À¿¡ ´ëÇÑ class
/// </summary>
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
	void Add(GameObject* gameObject);//¾À¿¡ Ãß°¡
	void Remove(GameObject* gameObject);//¾À¿¡¼­ Á¦°Å
public: 
	template<typename T>
	void Hold(); //GameObject¸¦ »ó¼Ó¹Þ´Â °³Ã¼¸¦ ¾ÀÀÇ ¹­¾îµÒ
public:
	vector<GameObject*> gameObjectList;
	vector<GameObject*>::iterator gameObjectIter;
	vector<function<void()> >holdList;
	vector<function<void()> >::iterator holdIter;
};

template<typename T>
void Scene::Hold()
{
	holdList.push_back([this]() {
		Add(new T());
	});
};