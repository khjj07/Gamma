#pragma once
#include <string>
/// <summary>
/// 디버그용 클래스
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
/// 디버그 스크립트 클래스
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