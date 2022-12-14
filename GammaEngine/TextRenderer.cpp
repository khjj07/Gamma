#include "stdafx.h"

TextRenderer::TextRenderer()
{

}

TextRenderer::TextRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
	text = string("");
	DirectXModule* dxModule = DirectXModule::Instance();
	textFormat = dxModule->textFormatList.at(0);
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
		int len = text.size() - 1;
		renderTarget->DrawText(
			ToTCHAR(text),
			len,
			textFormat,
			RectF(renderPos.x, renderPos.y, renderPos.x + renderSize.x, renderPos.y + renderSize.y),
			pen
		);
	}
	
}