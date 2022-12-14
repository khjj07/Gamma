#pragma once
#include "Type.h"
class Renderer;
class Transform;

class RectangleRenderer : public Renderer
{
public:
	RectangleRenderer();
	RectangleRenderer(GameObject* g);
	~RectangleRenderer();
	virtual void Render();
public:


private:

};
