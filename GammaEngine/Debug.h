#pragma once
/// <summary>
/// ����׿� Ŭ����
/// </summary>
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
	DebugScript();
	DebugScript(GameObject*);
	~DebugScript();

public:
	virtual void Update();

public:
	string fps;
};