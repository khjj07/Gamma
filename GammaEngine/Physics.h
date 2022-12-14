#pragma once

/// <summary>
/// 레이케스팅의 결과에 대한 구조체
/// </summary>
struct RaycastResponse {
	bool hit; 
	float fraction;
	vector2 position; 
	vector2 normal;
	Collider* collider;
	GameObject* gameObject;
};

/// <summary>
/// 물리적인 기능을 포함하는 class
/// </summary>
class Physics
{
public:
	Physics();
	~Physics();

public:
	static bool InBound(rect2D rect,vector2 v);//v가 rect안에 포함된다면 true를 반환
	static RaycastResponse Raycast(vector2 from, vector2 to, string tag);//정해진 지점 사이에 충돌체가 존재한다면 true 반환
	static RaycastResponse Raycast(vector2 from, vector2 to, vector<string> tag);//정해진 지점 사이에 충돌체가 존재한다면 true 반환
};
