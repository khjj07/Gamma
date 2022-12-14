#pragma once

/// <summary>
/// �����ɽ����� ����� ���� ����ü
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
/// �������� ����� �����ϴ� class
/// </summary>
class Physics
{
public:
	Physics();
	~Physics();

public:
	static bool InBound(rect2D rect,vector2 v);//v�� rect�ȿ� ���Եȴٸ� true�� ��ȯ
	static RaycastResponse Raycast(vector2 from, vector2 to, string tag);//������ ���� ���̿� �浹ü�� �����Ѵٸ� true ��ȯ
	static RaycastResponse Raycast(vector2 from, vector2 to, vector<string> tag);//������ ���� ���̿� �浹ü�� �����Ѵٸ� true ��ȯ
};
