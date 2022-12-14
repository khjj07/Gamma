#pragma once

class GameObject;

/// <summary>
/// ���� ���� class
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
	void Add(GameObject* gameObject);//���� �߰�
	void Remove(GameObject* gameObject);//������ ����
public: 
	template<typename T>
	void Hold(); //GameObject�� ��ӹ޴� ��ü�� ���� �����
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