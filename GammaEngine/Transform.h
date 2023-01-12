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
	class GammaEngineAPI Transform : public Component
	{
	public:
		Transform(GameObject* t);
		~Transform();
	public:
		vector2 GetWorldPosition();
		vector2 GetWorldScale(); 
		void SetWorldPosition(vector2 v);
		void SetWorldScale(vector2 v);
		Matrix3x3 GetWorldMatrix();
	public:
		vector2 position = vector2();
		float rotation = 0;
		vector2 scale = vector2(1, 1);
		Transform* parent = nullptr;
	};
}

