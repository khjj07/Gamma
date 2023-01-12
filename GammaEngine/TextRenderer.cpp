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
		Matrix3x3 matrix = Camera::main->Projection() * Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix();
		GraphicSystem::DrawTextBox(size,matrix, text,wstring(L"Verdana"), material);
	}
	
}