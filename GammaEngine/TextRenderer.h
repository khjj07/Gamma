#pragma once
#include "Type.h"
class Renderer;
class Transform;

/// <summary>
/// direct2d ȭ�鿡 �ؽ�Ʈ�� ����ϴ� ������Ʈ
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
