#include "stdafx.h"


Renderer::Renderer() : Component()
{
	DirectXModule* dxModule = DirectXModule::Instance();
	renderTarget = dxModule->renderTarget;
	dxModule->renderComponentList.push_back(this);
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Red, 1), (ID2D1SolidColorBrush**)&brush);
}


Renderer::Renderer(Transform* t) : Component(t)
{
	DirectXModule* dxModule = DirectXModule::Instance();
	renderTarget = dxModule->renderTarget;
	dxModule->renderComponentList.push_back(this);
	transform = t;
	size = vector2();
	offset = vector2();
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Red, 1), (ID2D1SolidColorBrush**)&brush);
}
Renderer::Renderer(Transform* t, vector2 s): Component(t)
{
	DirectXModule* dxModule = DirectXModule::Instance();
	renderTarget = dxModule->renderTarget;
	dxModule->renderComponentList.push_back(this);
	transform = t;
	size = s;
	offset = vector2();
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Red, 1), (ID2D1SolidColorBrush**)&brush);
}

Renderer::Renderer(Transform* t, vector2 s, vector2 o) : Component(t)
{
	DirectXModule* dxModule = DirectXModule::Instance();
	renderTarget = dxModule->renderTarget;
	dxModule->renderComponentList.push_back(this);
	transform = t;
	size = s;
	offset = o;
	renderTarget->CreateSolidColorBrush(ColorF(ColorF::Red, 1), (ID2D1SolidColorBrush**)&brush);
}

Renderer::~Renderer()
{
	brush->Release();
	DirectXModule* dxModule = DirectXModule::Instance();
	dxModule->renderComponentList.erase(remove_if(dxModule->renderComponentList.begin(), dxModule->renderComponentList.end(), [this](Component* x) { if (x == this) return true; else return false; }), dxModule->renderComponentList.end());
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