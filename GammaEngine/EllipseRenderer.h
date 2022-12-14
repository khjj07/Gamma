#pragma once
#include "Type.h"
class Renderer;
class Transform;
class EllipseRenderer : public Renderer
{
public:
	EllipseRenderer();
	EllipseRenderer(GameObject* t);
	~EllipseRenderer();
	virtual void Render();
public:


private:

};
