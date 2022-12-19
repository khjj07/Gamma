#include "stdafx.h"
#include "Direct2DModule.h"
#include "Render.h"

GraphicSystem::GraphicSystem()
{

}

GraphicSystem::~GraphicSystem()
{
	
}

void GraphicSystem::Initialize(HWND hWnd)
{
	Screen* screen = Screen::Instance();
	render = (RenderModule*)new Direct2DModule();
	render->Initialize(hWnd);
}

void  GraphicSystem::Frame()
{
	render->BeginDraw();
	
	vector<Renderer*> renderList = renderComponentList;
	sort(renderList.begin(), renderList.end(), [](Renderer* a, Renderer* b) {
		return a->order < b->order;
	});

	for(renderComponentIter = renderList.begin(); renderComponentIter < renderList.end(); renderComponentIter++)
	{
		(*renderComponentIter)->Render();
	}
	render->EndDraw();
}

void GraphicSystem::Resize(int width, int height)
{
	render->Resize(width, height);
}

void GraphicSystem::DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	render->DrawRectangle(pos, size, rotation, meterial);
}

void GraphicSystem::DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	render->DrawEllipse(pos, size, rotation, meterial);
}

void GraphicSystem::DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial)
{
	render->DrawLine(start, end, thickness, meterial);
}

void GraphicSystem::DrawTextBox(vector2 pos, vector2 size, string text, Meterial* meterial)
{
	render->DrawTextBox(pos, size, text, meterial);
}
