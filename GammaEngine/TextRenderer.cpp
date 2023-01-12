#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::TextRenderer::TextRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
	text = wstring(L"");
}

GammaEngine::TextRenderer::~TextRenderer()
{

}

void GammaEngine::TextRenderer::Render()
{
	if (text.length() > 0)
	{
		vector2 scale = transform->GetWorldScale();

		vector2 renderPos = transform->GetWorldPosition() + offset;
		vector2 renderSize = size;

		Renderer::Adjust(renderPos);
		GraphicSystem::DrawTextBox(renderSize,renderPos, scale, text,wstring(L"Verdana"), material);
	}
	
}