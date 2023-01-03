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
	vector2 scale = transform->GetWorldScale();

	vector2 renderPos = transform->GetWorldPosition() + offset;
	vector2 renderSize = size;

	renderSize.x = renderSize.x * scale.x;
	renderSize.y = renderSize.y * scale.y;
	Renderer::Adjust(renderPos, renderSize);
	GraphicSystem::DrawRectangle(renderPos, renderSize,transform->GetWorldRotation(),meterial);
}