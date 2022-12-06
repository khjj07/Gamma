#include "stdafx.h"

TextRenderer::TextRenderer()
{
}
TextRenderer::TextRenderer(Transform* t) :Renderer(t)
{
	size = vector2(100, 100);
	text = string("");
	DirectXModule* dxModule = DirectXModule::Instance();
	textFormat = dxModule->textFormatList.at(0);
}

TextRenderer::TextRenderer(Transform* t, vector2 s) :Renderer(t, s)
{

}

TextRenderer::TextRenderer(Transform* t, vector2 s, vector2 o) :Renderer(t, s, o)
{
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
		renderTarget->DrawText(
			ToTCHAR(text),
			text.length() - 1,
			textFormat,
			RectF(renderPos.x, renderPos.y, renderPos.x + renderSize.x, renderPos.y + renderSize.y),
			pen
		);
	}
	
}