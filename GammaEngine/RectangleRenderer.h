#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// 사각형 렌더러
/// </summary>
class RectangleRenderer : public Renderer
{
public:
	RectangleRenderer();
	RectangleRenderer(GameObject* g);
	~RectangleRenderer();

public:
	virtual void Render();
};
