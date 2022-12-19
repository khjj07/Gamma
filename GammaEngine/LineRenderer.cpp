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
    GraphicSystem::DrawLine(s, d, thickness, meterial);
}