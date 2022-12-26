#include "stdafx.h"
#pragma comment (lib, "windowscodecs.lib")
using namespace GammaEngine;
GammaEngine::BitmapRenderer::BitmapRenderer(GameObject* t) :Renderer(t)
{
	meterial->pen = vector4(0, 0, 0, 0);
	meterial->brush = vector4(1, 1, 1, 1);
}

GammaEngine::BitmapRenderer::~BitmapRenderer()
{

}

void GammaEngine::BitmapRenderer::LoadBitmapImage(wstring filename)
{
	bitmap = GraphicSystem::LoadBitmapImage(filename);
	size = GraphicSystem::GetBitmapSize(bitmap);
}

void GammaEngine::BitmapRenderer::Render()
{
	vector2 renderPos = transform->position + offset;
	vector2 renderSize = size;
	renderSize.x = renderSize.x * transform->scale.x;
	renderSize.y = renderSize.y * transform->scale.y;
	Renderer::Adjust(renderPos, renderSize);
	GraphicSystem::DrawBitmap(bitmap, renderPos, renderSize, transform->rotation, meterial);
}