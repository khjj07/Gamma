#pragma once

/// <summary>
/// ���� ���� class
/// </summary>

namespace GammaEngine
{
	class GammaEngineAPI Engine : public Singleton<Engine>
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

	GammaEngineAPI void Instantiate(GameObject* obj);//���� ���� ���ο� ������Ʈ�� �����ϴ� �Լ�
	GammaEngineAPI void Destroy(GameObject* obj);//���� ���� �ִ� ������Ʈ�� �����ϴ� �Լ�
	GammaEngineAPI bool CompareTag(GameObject* gameObject, string tag);//�±װ� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTag(GameObject* gameObject, char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTags(GameObject* gameObject, vector<string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
	GammaEngineAPI bool CompareTags(GameObject* gameObject, vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
}
