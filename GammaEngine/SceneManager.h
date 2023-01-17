#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>

namespace GammaEngine
{
	class GammaEngineAPI SceneManager
	{
	public: 
		friend class Engine;
		friend class ObjectManager;

	public:
		SceneManager();
		~SceneManager();

	public:
		void Initialize();
		static void AddScene(Scene* scene);
		static void LoadScene(int number);

	private:
		static vector<Scene*> sceneList;

	private:
		static Scene* currentScene;
	};
}
