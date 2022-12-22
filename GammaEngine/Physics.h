#pragma once

/// <summary>
/// 레이케스팅의 결과에 대한 구조체
/// </summary>
namespace GammaEngine
{
	struct GammaEngineAPI RaycastResponse {
		bool hit; //충돌여부
		float fraction; //레이캐스트 비율
		vector2 position; //충돌 위치
		vector2 normal; //법선 벡터
		Collider* collider; //충돌체
		GameObject* gameObject; //충돌체의 오브젝트
	};

	/// <summary>
	/// 물리적인 기능을 포함하는 class
	/// </summary>
	class GammaEngineAPI Physics
	{
	public:
		Physics();
		~Physics();

	public:
		static bool InBound(rect2D rect, vector2 v);//v가 rect안에 포함된다면 true를 반환
		static RaycastResponse Raycast(vector2 from, vector2 to, string tag);//정해진 지점 사이에 충돌체가 존재한다면 true 반환
		static RaycastResponse Raycast(vector2 from, vector2 to, vector<string> tag);//정해진 지점 사이에 충돌체가 존재한다면 true 반환

	private:
		static void GetRayCondition(vector2 from, vector2 v, Collider* col, float& objectRange, bool& OnDirection, bool& InRange);
	};
}