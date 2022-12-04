#include "stdafx.h"

LineRenderer::LineRenderer() :Renderer()
{
}
LineRenderer::LineRenderer(Transform* t) :Renderer(t)
{

}

LineRenderer::LineRenderer(Transform* t, vector2 s) :Renderer(t, s)
{

}

LineRenderer::LineRenderer(Transform* t, vector2 s, vector2 o) :Renderer(t, s, o)
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
    renderTarget->DrawLine(
        Point2F(s.x, s.y),
        Point2F(d.x, d.y),
        brush,
        0.5f,
        style
    );
}