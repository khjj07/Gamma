#pragma once

/// <summary>
/// 게임 엔진 class
/// </summary>

namespace GammaEngine
{
	class GammaEngineAPI Engine : public Singleton<Engine>
	{
	public:
		Engine();
		~Engine();

	public:
		void Initialize();
		bool Frame();

	public:
		SceneManager* sceneManager;
		ObjectManager* objectManager;
	};

}
