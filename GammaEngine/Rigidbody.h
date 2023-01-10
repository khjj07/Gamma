#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 위치 크기 회전 정보를 포함하는 컴포넌트
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Rigidbody : public Component
	{
	public:
		Rigidbody(GameObject* t);
		~Rigidbody();

	public:
		vector2 velocity;
	};
}

