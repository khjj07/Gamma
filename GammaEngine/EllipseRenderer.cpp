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
	vector2 scale = transform->GetWorldScale();

	vector2 renderPos = transform->GetWorldPosition() + offset;
	vector2 renderSize = size;
	Renderer::Adjust(renderPos, scale);
	GraphicSystem::DrawEllipse(renderSize, renderPos, scale, transform->GetWorldRotation(), material);
}