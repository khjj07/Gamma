#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// Ÿ�� ������
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
