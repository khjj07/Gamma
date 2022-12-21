#include "stdafx.h"

EllipseRenderer::EllipseRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

EllipseRenderer::~EllipseRenderer()
{

}
void EllipseRenderer::Render()
{
	vector2 renderPos = transform->position + offset;
	vector2 renderSize = size;
	renderSize.x = renderSize.x * transform->scale.x;
	renderSize.y = renderSize.y * transform->scale.y;
	Renderer::Adjust(renderPos, renderSize);

}