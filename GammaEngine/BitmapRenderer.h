#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
/// </summary>
class BitmapRenderer : public Renderer
{
public:
	BitmapRenderer();
	BitmapRenderer(GameObject* t);
	~BitmapRenderer();

public:
	virtual void Render();

public:
	int LoadBitmapImage(string filename);

public:
	IWICImagingFactory* factory;
	ID2D1Bitmap* bitmap;
};
