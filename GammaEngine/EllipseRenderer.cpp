#include "stdafx.h"

EllipseRenderer::EllipseRenderer() :Renderer()
{

}

EllipseRenderer::EllipseRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

EllipseRenderer::~EllipseRenderer()
{

}
void EllipseRenderer::Render()
{
	if (pen || brush)
	{
		vector2 renderPos = transform->position + offset;
		vector2 renderSize = size;
		renderSize.x = renderSize.x * transform->scale.x;
		renderSize.y = renderSize.y * transform->scale.y;
		Renderer::Adjust(renderPos, renderSize);
		D2D1_ELLIPSE ellipse;
		ellipse.radiusX = renderSize.x / 2;
		ellipse.radiusY = renderSize.y / 2;
		ellipse.point.x = renderPos.x;
		ellipse.point.y = renderPos.y;
		D2D1_POINT_2F center = { renderPos.x,  renderPos.y };
		renderTarget->SetTransform(Matrix3x2F::Rotation(transform->rotation, center));
		if (pen)
		{
			renderTarget->DrawEllipse(ellipse, pen);
		}
		if (brush)
		{
			renderTarget->FillEllipse(ellipse, brush);
		}
	}

}