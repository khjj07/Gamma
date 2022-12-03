#pragma once
#include "Type.h"
#include <vector>
using namespace std;

class Component;
class GameObject;
class Transform : public Component
{
public:
	Transform();
	Transform(GameObject*);
	~Transform();
public:
	vector2 position = vector2();
	float rotation = 0;
	vector2 scale = vector2(1,1);
	Transform* parent=nullptr;
	GameObject* gameObject;
public:
	template<typename T>
	T* GetComponent()
	{
		return gameObject->GetComponent<T>();
	}
	template<typename T>
	void AddComponent()
	{
		gameObject->AddComponent<T>();
	}
};
