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
	/// 게임 오브젝트 class
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
		bool CompareTag(string tag);//태그가 일치하면 true 반환
		bool CompareTag(char* tag);//태그가 일치하면 true 반환
		bool CompareTags(vector<string> tags);//태그가 하나라도 일치하면 true 반환
		bool CompareTags(vector<char*> tags);//태그가 하나라도 일치하면 true 반환

	public:
		Transform* transform;
		string* tag;
		bool isStarted = false;
		bool isEnabled = true;

	public:
		vector<Component*>* componentList;

	public:
		template<typename T>
		T* GetComponent(); //오브젝트에 있는 컴포넌트의 참조를 반환
		template<typename T>
		void AddComponent(); //오브젝트를 새로 추가
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
