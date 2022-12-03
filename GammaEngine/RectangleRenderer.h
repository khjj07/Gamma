#pragma once
#include "Type.h"
class Renderer;
class Transform;
class RectangleRenderer : public Renderer
{
public:
	RectangleRenderer();
	RectangleRenderer(Transform* t);
	RectangleRenderer(Transform* t, vector2);
	RectangleRenderer(Transform* t, vector2, vector2);
	~RectangleRenderer();
	virtual void Render();
public:


private:

};
