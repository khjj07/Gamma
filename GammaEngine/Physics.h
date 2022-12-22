#pragma once

/// <summary>
/// �����ɽ����� ����� ���� ����ü
/// </summary>
namespace GammaEngine
{
	struct GammaEngineAPI RaycastResponse {
		bool hit; //�浹����
		float fraction; //����ĳ��Ʈ ����
		vector2 position; //�浹 ��ġ
		vector2 normal; //���� ����
		Collider* collider; //�浹ü
		GameObject* gameObject; //�浹ü�� ������Ʈ
	};

	/// <summary>
	/// �������� ����� �����ϴ� class
	/// </summary>
	class GammaEngineAPI Physics
	{
	public:
		Physics();
		~Physics();

	public:
		static bool InBound(rect2D rect, vector2 v);//v�� rect�ȿ� ���Եȴٸ� true�� ��ȯ
		static RaycastResponse Raycast(vector2 from, vector2 to, string tag);//������ ���� ���̿� �浹ü�� �����Ѵٸ� true ��ȯ
		static RaycastResponse Raycast(vector2 from, vector2 to, vector<string> tag);//������ ���� ���̿� �浹ü�� �����Ѵٸ� true ��ȯ

	private:
		static void GetRayCondition(vector2 from, vector2 v, Collider* col, float& objectRange, bool& OnDirection, bool& InRange);
	};
}