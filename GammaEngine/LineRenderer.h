#pragma once
#include "Type.h"
class Renderer;
class Transform;
class LineRenderer : public Renderer
{
public:
	LineRenderer();
	LineRenderer(GameObject* t);
	~LineRenderer();
	virtual void Render();
public:
	vector2 src;
	vector2 dst;
	ID2D1StrokeStyle* style=nullptr;
private:

};
