#include "stdafx.h"

RectangleRenderer::RectangleRenderer() :Renderer()
{
}
RectangleRenderer::RectangleRenderer(Transform* t) :Renderer(t)
{
	size = vector2(100, 100);
}

RectangleRenderer::RectangleRenderer(Transform* t, vector2 s) :Renderer(t, s)
{

}

RectangleRenderer::RectangleRenderer(Transform* t, vector2 s, vector2 o) :Renderer(t, s, o)
{
}

RectangleRenderer::~RectangleRenderer()
{

}
void RectangleRenderer::Render()
{
	if (pen||brush)
	{
		vector2 renderPos = transform->position + offset;
		vector2 renderSize = size;
		renderSize.x = renderSize.x * transform->scale.x;
		renderSize.y = renderSize.y * transform->scale.y;
		Renderer::Adjust(renderPos, renderSize);
		D2D1_RECT_F rectangle;
		D2D1_POINT_2F center = { renderPos.x,  renderPos.y };
		rectangle.left = renderPos.x - renderSize.x / 2;
		rectangle.top = renderPos.y - renderSize.y / 2;
		rectangle.right = renderPos.x + renderSize.x / 2;
		rectangle.bottom = renderPos.y + renderSize.y / 2;


		renderTarget->SetTransform(Matrix3x2F::Rotation(transform->rotation, center));
		if (pen)
		{
			renderTarget->DrawRectangle(rectangle, pen);
		}
		if (brush)
		{
			renderTarget->FillRectangle(rectangle, brush);

		}
	}
}