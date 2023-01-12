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
	Renderer::Adjust(renderPos, scale);
	GraphicSystem::DrawRectangle(renderSize,renderPos, scale,transform->GetWorldRotation(), material);
}