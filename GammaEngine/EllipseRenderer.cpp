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

	renderSize.x = renderSize.x * scale.x;
	renderSize.y = renderSize.y * scale.y;
	Renderer::Adjust(renderPos, renderSize);
	GraphicSystem::DrawEllipse(renderPos, renderSize, transform->GetWorldRotation(), meterial);
}