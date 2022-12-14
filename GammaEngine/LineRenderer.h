#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// ∂Û¿Œ ∑ª¥ı∑Ø
/// </summary>
class LineRenderer : public Renderer
{
public:
	LineRenderer();
	LineRenderer(GameObject* t);
	~LineRenderer();

public:
	virtual void Render();

public:
	vector2 src;
	vector2 dst;
	ID2D1StrokeStyle* style=nullptr;
};
