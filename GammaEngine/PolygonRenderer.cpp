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
	Matrix3x3 matrix = Camera::main->Projection() * Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix();
	GraphicSystem::DrawPolygon(name, matrix, material);
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