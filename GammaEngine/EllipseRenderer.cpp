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
	vector2 renderPos = transform->position + offset;
	vector2 renderSize = size;
	renderSize.x = renderSize.x * transform->scale.x;
	renderSize.y = renderSize.y * transform->scale.y;
	Renderer::Adjust(renderPos, renderSize);
	GraphicSystem::DrawEllipse(renderPos, renderSize, transform->rotation, meterial);
}