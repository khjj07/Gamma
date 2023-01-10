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
	class GammaEngineAPI Rigidbody : public Component
	{
	public:
		Rigidbody(GameObject* t);
		~Rigidbody();

	public:
		vector2 velocity;
	};
}

