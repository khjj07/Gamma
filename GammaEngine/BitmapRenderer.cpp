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
	Matrix3x3 matrix = Camera::main->Projection() * Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix();
	GraphicSystem::DrawBitmap(bitmap, size, matrix, material);
}