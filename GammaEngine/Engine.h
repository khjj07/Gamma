#pragma once

/// <summary>
/// ���� ���� class
/// </summary>
class Engine : public Singleton<Engine>
{
public:
	Engine();
	~Engine();

public:
	void Initialize(Scene*);
	bool Frame();

public:
	Scene* currentScene;
	Scene* nextScene;
	vector<GameObject*> addBuffer;//������Ʈ ������ ���� ����
	vector<GameObject*> removeBuffer;//���ŵ� ������Ʈ�� ���� ����
	vector<GameObject*>::iterator gameObjectIter;
};

extern void Instantiate(GameObject* obj);//���� ���� ���ο� ������Ʈ�� �����ϴ� �Լ�
extern void Destroy(GameObject* obj);//���� ���� �ִ� ������Ʈ�� �����ϴ� �Լ�
