#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// �簢�� ������
/// </summary>
class RectangleRenderer : public Renderer
{
public:
	RectangleRenderer(GameObject* g);
	~RectangleRenderer();

public:
	virtual void Render();
};
