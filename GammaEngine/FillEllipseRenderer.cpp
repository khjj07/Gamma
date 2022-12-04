#include "stdafx.h"

FillEllipseRenderer::FillEllipseRenderer() :Renderer()
{
}
FillEllipseRenderer::FillEllipseRenderer(Transform* t) :Renderer(t)
{
	size = vector2(100, 100);
}

FillEllipseRenderer::FillEllipseRenderer(Transform* t,vector2 s) :Renderer(t,s)
{

}

FillEllipseRenderer::FillEllipseRenderer(Transform* t,vector2 s,vector2 o) :Renderer(t,s,o)
{
}

FillEllipseRenderer::~FillEllipseRenderer()
{

}
void FillEllipseRenderer::Render()
{
	vector2 renderPos=transform->position+offset;
	vector2 renderSize = size;
	renderSize.x = renderSize.x * transform->scale.x;
	renderSize.y = renderSize.y * transform->scale.y;
	Renderer::Adjust(renderPos, renderSize);
	D2D1_ELLIPSE ellipse;
	ellipse.radiusX = renderSize.x/2;
	ellipse.radiusY = renderSize.y/2;
	ellipse.point.x = renderPos.x;
	ellipse.point.y = renderPos.y;
	D2D1_POINT_2F center = { renderPos.x,  renderPos.y };
	renderTarget->SetTransform(Matrix3x2F::Rotation(transform->rotation, center));
	renderTarget->FillEllipse(ellipse, brush);
}