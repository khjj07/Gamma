#pragma once
struct vector2;
struct rect2D;

struct RaycastResponse {
	bool hit; 
	float fraction;
	vector2 position; 
	vector2 normal;
	Collider* collider;
	GameObject* gameObject;
};

class Physics
{
public:
	Physics();
	~Physics();
public:
	static bool InBound(rect2D,vector2);
	static RaycastResponse Raycast(vector2, vector2, string);
	static RaycastResponse Raycast(vector2, vector2,vector<string>);
private:

};
