#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::PolygonRenderer::PolygonRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

GammaEngine::PolygonRenderer::~PolygonRenderer()
{

}

void GammaEngine::PolygonRenderer::Render()
{
	vector2 scale = transform->GetWorldScale();

	vector2 renderPos = transform->GetWorldPosition() + offset;
	
	Renderer::Adjust(renderPos, scale);
	GraphicSystem::DrawPolygon(name, renderPos, scale, transform->GetWorldRotation(), material);
}

void GammaEngine::PolygonRenderer::SetPoints(vector<vector2> newPoints)
{
	points=newPoints;
}

void GammaEngine::PolygonRenderer::AddPoints(vector2 point)
{
	points.push_back(point);
}

void GammaEngine::PolygonRenderer::MakePolygon(wstring n)
{
	name = GraphicSystem::MakePolygon(n, points);
}