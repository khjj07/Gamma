#pragma once
#include "Type.h"
class Renderer;
class Transform;
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(Transform* t);
	TextRenderer(Transform* t, vector2);
	TextRenderer(Transform* t, vector2, vector2);
	~TextRenderer();
	virtual void Render();
public:
	string text=string("");
	IDWriteTextFormat* textFormat;
private:

};
