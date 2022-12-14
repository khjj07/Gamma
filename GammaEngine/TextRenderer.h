#pragma once
#include "Type.h"
class Renderer;
class Transform;
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(GameObject* t);
	~TextRenderer();
	virtual void Render();
public:
	string text=string("");
	IDWriteTextFormat* textFormat;
private:

};
