#pragma once
class Component;
class Transform;
class Camera : public Component
{
public:
	Camera();
	Camera(Transform* t);
	~Camera();
public:
	vector2 ScreenToWorldPoint(vector2);
public:
	static Camera* main;
	float orthoScale=1;
private:

};
