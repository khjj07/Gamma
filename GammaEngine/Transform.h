#pragma once

/// <summary>
/// 위치 크기 회전 정보를 포함하는 컴포넌트
/// </summary>
class Transform : public Component
{
public:
	Transform();
	Transform(GameObject* t);
	~Transform();

public:
	vector2 position = vector2();
	float rotation = 0;
	vector2 scale = vector2(1,1);
	Transform* parent=nullptr;
};
