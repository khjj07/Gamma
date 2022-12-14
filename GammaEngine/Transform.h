#pragma once

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
