#include "stdafx.h"

LineRenderer::LineRenderer() :Renderer()
{
}

LineRenderer::LineRenderer(GameObject* t) :Renderer(t)
{

}

LineRenderer::~LineRenderer()
{

}
void LineRenderer::Render()
{
    vector2 s = src;
    vector2 d = dst;

    Adjust(s);
    Adjust(d);
    if (pen)
    {
        renderTarget->DrawLine(
            Point2F(s.x, s.y),
            Point2F(d.x, d.y),
            pen,
            0.5f,
            style
        );
    }
}