#pragma once

/// <summary>
/// 디버그 스크립트 클래스
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