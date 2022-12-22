#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine {
	class GameObject;
	class Transform;
	struct CollisionResponse;

	/// <summary>
	/// ÄÄÆ÷³ÍÆ® class
	/// </summary>
	class GammaEngineAPI Component abstract
	{
	public:
		Component(GameObject* g);
		virtual ~Component();

	public:
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void OnDestroy();
		virtual void OnDisable();
		virtual void OnEnable();
		virtual void OnCollisionEnter(CollisionResponse response);
		virtual void OnCollisionStay(CollisionResponse response);
		virtual void OnCollisionExit(CollisionResponse response);
	private:
		vector<Component*>& componentList;

	public:
		template<typename T>
		T* GetComponent();
		template<typename T>
		void AddComponent();

	public:
		GameObject* gameObject;
		Transform* transform;
	};

	template<typename T>
	T* Component::GetComponent()
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
	void Component::AddComponent()
	{
		T* newComponent = new T(this);
		componentList.push_back(newComponent);
	}

}
