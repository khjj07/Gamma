#include "stdafx.h"


Renderer::Renderer() : Component()
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	renderTarget = graphic->renderTarget;
	graphic->renderComponentList.push_back(this);
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Black, 1), (ID2D1SolidColorBrush**)&pen);
}

Renderer::Renderer(GameObject* t) : Component(t)
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	renderTarget = graphic->renderTarget;
	graphic->renderComponentList.push_back(this);
	size = vector2();
	offset = vector2();
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Black, 1), (ID2D1SolidColorBrush**)&pen);
}

Renderer::~Renderer()
{
	if (pen)
	{
		pen->Release();
	}
	if (brush)
	{
		brush->Release();
	}
	GraphicSystem* graphic = GraphicSystem::Instance();
	graphic->renderComponentList.erase(remove_if(graphic->renderComponentList.begin(), graphic->renderComponentList.end(), [this](Component* x) { if (x == this) return true; else return false; }), graphic->renderComponentList.end());
}

template<>
void Renderer::SetBrush<ID2D1SolidColorBrush>(long color, float alpha)
{
	if (brush)
	{
		brush->Release();
	}
	renderTarget->CreateSolidColorBrush(ColorF(color, alpha), (ID2D1SolidColorBrush**)&brush);
}

template<>
void Renderer::SetBrush<ID2D1LinearGradientBrush>(ID2D1GradientStopCollection* stops)
{
	if (brush)
	{
		brush->Release();
	}
	vector2 pos = transform->position;
	vector2 scale = transform->scale;
	renderTarget->CreateLinearGradientBrush(LinearGradientBrushProperties(Point2F(pos.x+offset.x, pos.y + offset.y),
	Point2F(pos.x + offset.x +size.x*scale.x, pos.y + offset.y + size.y * scale.y)),stops,(ID2D1LinearGradientBrush**) &brush);
}

template<>
void Renderer::SetPen<ID2D1SolidColorBrush>(long color, float alpha)
{
	if (pen)
	{
		pen->Release();
	}
	renderTarget->CreateSolidColorBrush(ColorF(color, alpha), (ID2D1SolidColorBrush**)&pen);
}

template<>
void Renderer::SetPen<ID2D1LinearGradientBrush>(ID2D1GradientStopCollection* stops)
{
	if (pen)
	{
		pen->Release();
	}
	vector2 pos = transform->position;
	vector2 scale = transform->scale;
	renderTarget->CreateLinearGradientBrush(LinearGradientBrushProperties(Point2F(pos.x + offset.x, pos.y + offset.y),
		Point2F(pos.x + offset.x + size.x * scale.x, pos.y + offset.y + size.y * scale.y)), stops, (ID2D1LinearGradientBrush**)&pen);
}

void Renderer::Adjust(vector2& v)
{
	if (Camera::main)
	{
		vector2 center = vector2(Screen::width / 2, Screen::height / 2) - Camera::main->transform->position;

		v = v / Camera::main->orthoScale + center;
	}
	else
	{
		v = v + vector2(Screen::width / 2, Screen::height / 2);
	}
}

void Renderer::Adjust(vector2& pos,vector2& size)
{
	if (Camera::main)
	{
		vector2 center = vector2(Screen::width / 2, Screen::height / 2) - Camera::main->transform->position;
			
		pos = pos / Camera::main->orthoScale + center;
		

		size = size / Camera::main->orthoScale;
	}
	else
	{
		pos = pos + vector2(Screen::width / 2, Screen::height / 2);
	}
}