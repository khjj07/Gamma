#pragma once

/// <summary>
/// ����׿� Ŭ����
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
/// ����� ��ũ��Ʈ Ŭ����
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