#include "stdafx.h"
#pragma comment (lib, "windowscodecs.lib")
using namespace GammaEngine;
GammaEngine::BitmapRenderer::BitmapRenderer(GameObject* t) :Renderer(t)
{
	material->pen = vector4(0, 0, 0, 0);
	material->brush = vector4(1, 1, 1, 1);
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
	vector2 scale = transform->GetWorldScale();

	vector2 renderPos = transform->GetWorldPosition() + offset;
	vector2 renderSize = size;

	Renderer::Adjust(renderPos, scale);
	GraphicSystem::DrawBitmap(bitmap, renderSize, renderPos, scale, transform->GetWorldRotation(), material);
}