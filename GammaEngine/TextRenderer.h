#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// direct2d 화면에 텍스트를 출력하는 컴포넌트
/// </summary>
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(GameObject* t);
	~TextRenderer();
	virtual void Render();
public:
	string text=string("");
private:

};
