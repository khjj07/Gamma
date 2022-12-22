#pragma once

/// <summary>
/// 디버그용 클래스
/// </summary>
using namespace GammaEngine;
class Debug : public GammaEngine::GameObject
{
public:
	Debug();
	~Debug();

private:

};

/// <summary>
/// 디버그 스크립트 클래스
/// </summary>
class DebugScript : public GammaEngine::Component
{
public:
	DebugScript(GameObject*);
	~DebugScript();

public:
	virtual void Update();

public:
	string fps;
};