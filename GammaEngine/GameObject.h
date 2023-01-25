#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif



namespace GammaEngine 
{
	class Component;

	/// <summary>
	/// ���� ������Ʈ class
	/// </summary>
	class GammaEngineAPI GameObject
	{
	public:
		GameObject();
		GameObject(const GameObject& obj);
		~GameObject();

	public:
		void Start();
		void Update();
		void LateUpdate();
		void OnDestroy();
		void OnDisable();
		void OnEnable();
		void OnCollisionEnter(CollisionResponse response);
		void OnCollisionStay(CollisionResponse response);
		void OnCollisionExit(CollisionResponse response);
		bool CompareTag(string tag);//�±װ� ��ġ�ϸ� true ��ȯ
		bool CompareTag(char* tag);//�±װ� ��ġ�ϸ� true ��ȯ
		bool CompareTags(vector<string> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ
		bool CompareTags(vector<char*> tags);//�±װ� �ϳ��� ��ġ�ϸ� true ��ȯ

	public:
		Transform* transform;
		string* tag;
		bool isStarted = false;
		bool isEnabled = true;

	public:
		vector<Component*>* componentList;

	public:
		template<typename T>
		T* GetComponent(); //������Ʈ�� �ִ� ������Ʈ�� ������ ��ȯ
		template<typename T>
		void AddComponent(); //������Ʈ�� ���� �߰�
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		for (auto iter = componentList->begin(); iter < componentList->end(); iter++)
		{
			if (strcmp(typeid(T).name(), typeid(**iter).name()) == 0)
				return (T*)*iter;
		}
		return nullptr;
	}

	template<typename T>
	void GameObject::AddComponent()
	{
		T* newComponent = new T(this);
		componentList->push_back(newComponent);
	}
}
