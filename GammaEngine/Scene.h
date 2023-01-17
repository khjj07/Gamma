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
	/// ���� ���� class
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
		void Add(GameObject* gameObject);//���� �߰�
		void Remove(GameObject* gameObject);//������ ����

	public:
		void Hold(GameObject* obj); //GameObject�� ��ӹ޴� ��ü�� ���� �����

	public:
		vector<GameObject*> gameObjectList;
		vector<GameObject*> holdList;
	};

	
}
