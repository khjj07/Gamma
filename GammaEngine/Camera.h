#pragma once
class Component;
class Transform;
class Camera : public Component
{
public:
	Camera();
	Camera(GameObject* t);
	~Camera();
public:
	vector2 ScreenToWorldPoint(vector2);
	vector2 WorldToScreenPoint(vector2 p);
	vector2 ScreenToWorldScale(vector2 s);
public:
	static Camera* main;
	float orthoScale=1;
private:

};
