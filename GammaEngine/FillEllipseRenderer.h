#pragma once
#include "Type.h"
class Renderer;
class Transform;
class FillEllipseRenderer : public Renderer
{
public:
	FillEllipseRenderer();
	FillEllipseRenderer(Transform* t);
	FillEllipseRenderer(Transform* t,vector2);
	FillEllipseRenderer(Transform* t, vector2, vector2);
	~FillEllipseRenderer();
	virtual void Render();
public:


private:

};
