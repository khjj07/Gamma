#pragma once
#include <d2d1.h>
#include "Type.h"

using namespace D2D1;
class Transform;
class Component;

/// <summary>
/// ·»´õ·¯ ÄÄÆ÷³ÍÆ®
/// </summary>
class Renderer : public Component
{
public:
	Renderer(GameObject* g);
	~Renderer();

public:
	virtual void Render() abstract;
	void Adjust(vector2& v);
	void Adjust(vector2& pos, vector2& size);

public:
	void SetBrush(vector4);
	void SetPen(vector4);

public:
	vector2 size;
	vector2 offset;
	Meterial* meterial;
	int order = 0;
};

