#pragma once
#include "Type.h"
class Renderer;
class Transform;
class BitmapRenderer : public Renderer
{
public:
	BitmapRenderer();
	BitmapRenderer(Transform* t);
	BitmapRenderer(Transform* t, vector2);
	BitmapRenderer(Transform* t, vector2, vector2);
	~BitmapRenderer();
	virtual void Render();
	int LoadBitmapImage(string filename);
public:
	IWICImagingFactory* factory;
	ID2D1Bitmap* bitmap;
private:

};
