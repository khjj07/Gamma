#include "stdafx.h"

TextRenderer::TextRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
	text = string("");
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Render()
{
	if (text.length() > 0)
	{
		vector2 renderPos = transform->position + offset;
		vector2 renderSize = size;
		renderSize.x = renderSize.x * transform->scale.x;
		renderSize.y = renderSize.y * transform->scale.y;
		Renderer::Adjust(renderPos);
		GraphicSystem::DrawTextBox(renderPos, renderSize, text,meterial);
	}
	
}