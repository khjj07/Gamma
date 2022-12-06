#pragma once
#include "Type.h"
class Renderer;
class Transform;
class EllipseRenderer : public Renderer
{
public:
	EllipseRenderer();
	EllipseRenderer(Transform* t);
	EllipseRenderer(Transform* t,vector2);
	EllipseRenderer(Transform* t, vector2, vector2);
	~EllipseRenderer();
	virtual void Render();
public:


private:

};
