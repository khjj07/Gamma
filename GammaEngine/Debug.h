#pragma once
#include <string>
/// <summary>
/// ����׿� Ŭ����
/// </summary>

using namespace std;
class Debug : public GameObject
{
public:
	Debug();
	~Debug();

private:

};

/// <summary>
/// ����� ��ũ��Ʈ Ŭ����
/// </summary>
class DebugScript : public Component
{
public:
	DebugScript(GameObject*);
	~DebugScript();

public:
	virtual void Update();

public:
	wstring fps;
};