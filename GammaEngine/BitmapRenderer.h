#pragma once
#include "Type.h"
class Renderer;
class Transform;
class BitmapRenderer : public Renderer
{
public:
	BitmapRenderer();
	BitmapRenderer(GameObject* t);

	~BitmapRenderer();
	virtual void Render();
	int LoadBitmapImage(string filename);
public:
	IWICImagingFactory* factory;
	ID2D1Bitmap* bitmap;
private:

};
