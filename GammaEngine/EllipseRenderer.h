#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// Å¸¿ø ·»´õ·¯
/// </summary>
class EllipseRenderer : public Renderer
{
public:
	EllipseRenderer();
	EllipseRenderer(GameObject* t);
	~EllipseRenderer();

public:
	virtual void Render();
};
