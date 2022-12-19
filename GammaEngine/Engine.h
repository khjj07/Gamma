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
extern bool CompareTag(GameObject* gameObject, string tag);//�±װ� ��ġ�ϸ� true ��ȯ
extern bool CompareTag(GameObject* gameObject, char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
extern bool CompareTags(GameObject* gameObject, vector<string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
extern bool CompareTags(GameObject* gameObject, vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ