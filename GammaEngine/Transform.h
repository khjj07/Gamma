#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// ��ġ ũ�� ȸ�� ������ �����ϴ� ������Ʈ
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Transform : public Component
	{
	public:
		Transform(GameObject* t);
		~Transform();
	public:
		vector2 GetWorldPosition();
		float GetWorldRotation();
		vector2 GetWorldScale(); 
		void SetWorldPosition(vector2 v);
		void SetWorldRotation(float x);
		void SetWorldScale(vector2 v);

	public:
		vector2 position = vector2();
		float rotation = 0;
		vector2 scale = vector2(1, 1);
		Transform* parent = nullptr;
	};
}

