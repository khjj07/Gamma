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
	Renderer();
	Renderer(GameObject* g);
	~Renderer();

public:
	virtual void Render() abstract;
	void Adjust(vector2& v);
	void Adjust(vector2& pos, vector2& size);

public:
	template<class T>
	void SetBrush(long color, float alpha);

	template<class T>
	void SetBrush(ID2D1GradientStopCollection* stops);

	template<class T>
	void SetPen(long color, float alpha);

	template<class T>
	void SetPen(ID2D1GradientStopCollection* stops);
public:
	ID2D1HwndRenderTarget* renderTarget;
	vector2 size;
	vector2 offset;
	Metrerial* meterial;
	int order = 0;
};

