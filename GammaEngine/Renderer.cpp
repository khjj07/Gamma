#include "stdafx.h"


Renderer::Renderer() : Component()
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	graphic->renderComponentList.push_back(this);
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Black, 1), (ID2D1SolidColorBrush**)&pen);
}

Renderer::Renderer(GameObject* t) : Component(t)
{
	GraphicSystem* graphic = GraphicSystem::Instance();
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