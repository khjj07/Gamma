#pragma once

/// <summary>
/// ����� ��ũ��Ʈ Ŭ����
/// </summary>
using namespace GammaEngine;
class DebugScript : public GammaEngine::Component
{
public:
	DebugScript(GameObject*);
	~DebugScript();

public:
	virtual void Update();

public:
	wstring fps;
};