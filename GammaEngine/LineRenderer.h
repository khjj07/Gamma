#pragma once
#include "Type.h"
class Renderer;
class Transform;
class LineRenderer : public Renderer
{
public:
	LineRenderer();
	LineRenderer(Transform* t);
	LineRenderer(Transform* t, vector2);
	LineRenderer(Transform* t, vector2, vector2);
	~LineRenderer();
	virtual void Render();
public:
	vector2 src;
	vector2 dst;
	ID2D1StrokeStyle* style=nullptr;
private:

};
