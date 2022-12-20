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
	virtual void Render() abstract;

public:
	void LoadBitmapImage(string filename);

public:
	string bitmap;
};
