#pragma once
#include <d2d1.h>
#include "Type.h"

using namespace D2D1;
class Transform;
class Component;

class Renderer : public Component
{
public:
	Renderer();
	Renderer(GameObject* g);
	~Renderer();
public:
	template<class T>
	void SetBrush(long color, float alpha);
	template<class T>
	void SetBrush(ID2D1GradientStopCollection* stops);
	template<class T>
	void SetPen(long color, float alpha);
	template<class T>
	void SetPen(ID2D1GradientStopCollection* stops);
	void Adjust(vector2& v);
	void Adjust(vector2& pos, vector2& size);
public:
	vector2 size;
	vector2 offset;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1Brush* pen = 0;
	ID2D1Brush* brush = 0;
	int order=0;
};

