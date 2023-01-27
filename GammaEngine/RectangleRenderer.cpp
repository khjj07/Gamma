#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::RectangleRenderer::RectangleRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

GammaEngine::RectangleRenderer::~RectangleRenderer()
{

}

void GammaEngine::RectangleRenderer::Render()
{
	Matrix3x3 matrix = Camera::main->Projection() * transform->GetWorldMatrix() * Matrix3x3::Translation(offset.x, offset.y);
	GraphicSystem::DrawRectangle(size, matrix, material);
}