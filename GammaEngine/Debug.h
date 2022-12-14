#pragma once
/// <summary>
/// 디버그용 클래스
/// </summary>
class Debug : public GameObject
{
public:
	Debug();
	~Debug();

private:

};

/// <summary>
/// 디버그 스크립트 클래스
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