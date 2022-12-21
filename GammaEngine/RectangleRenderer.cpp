#include "stdafx.h"

RectangleRenderer::RectangleRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

RectangleRenderer::~RectangleRenderer()
{

}

void RectangleRenderer::Render()
{
	vector2 renderPos = transform->position + offset;
	vector2 renderSize = size;
	renderSize.x = renderSize.x * transform->scale.x;
	renderSize.y = renderSize.y * transform->scale.y;
	Renderer::Adjust(renderPos, renderSize);
	GraphicSystem::DrawRectangle(renderPos, renderSize,transform->rotation,meterial);
}