#include "stdafx.h"

GammaEngine::EllipseRenderer::EllipseRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

GammaEngine::EllipseRenderer::~EllipseRenderer()
{

}
void GammaEngine::EllipseRenderer::Render()
{
	Matrix3x3 matrix = Camera::main->Projection() * transform->GetWorldMatrix() * Matrix3x3::Translation(offset.x, offset.y);

	GraphicSystem::DrawEllipse(size, matrix, material);
}