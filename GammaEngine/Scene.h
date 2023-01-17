#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	class GameObject;

	/// <summary>
	/// ¾À¿¡ ´ëÇÑ class
	/// </summary>
	class GammaEngineAPI Scene
	{
	public:
		Scene();
		~Scene();

	public:
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
		void Hold(GameObject* obj); //GameObject¸¦ »ó¼Ó¹Þ´Â °³Ã¼¸¦ ¾ÀÀÇ ¹­¾îµÒ

	public:
		vector<GameObject*> gameObjectList;
		vector<GameObject*> holdList;
	};

	
}
