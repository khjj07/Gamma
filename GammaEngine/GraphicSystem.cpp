#include "stdafx.h"
#include "Direct2DModule.h"
#include "Render.h"

using namespace GammaEngine;
RenderModule* GammaEngine::GraphicSystem::render = nullptr;
GammaEngine::GraphicSystem::GraphicSystem()
{

}

GammaEngine::GraphicSystem::~GraphicSystem()
{
	
}

void GammaEngine::GraphicSystem::Initialize(HWND hWnd)
{
	Screen* screen = Screen::Instance();
	render = new Direct2DModule();
	render->Initialize(hWnd);
}

void GammaEngine::GraphicSystem::Release()
{
	render->Release();
}

void GammaEngine::GraphicSystem::Frame()
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

void GammaEngine::GraphicSystem::Resize(int width, int height)
{
	render->Resize(width, height);
}

void GammaEngine::GraphicSystem::DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	render->DrawRectangle(pos, size, rotation, meterial);
}

void GammaEngine::GraphicSystem::DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	render->DrawEllipse(pos, size, rotation, meterial);
}

void GammaEngine::GraphicSystem::DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial)
{
	render->DrawLine(start, end, thickness, meterial);
}

void GammaEngine::GraphicSystem::DrawTextBox(vector2 pos, vector2 size, string text, string fontFamily, Meterial* meterial)
{
	render->DrawTextBox(pos, size, text, fontFamily, meterial);
}

void GammaEngine::GraphicSystem::DrawBitmap(string bitmap, vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	render->DrawBitmap(bitmap,pos, size, rotation, meterial);
}

string GammaEngine::GraphicSystem::LoadBitmapImage(string filename)
{
	return render->LoadBitmapImage(filename);
}

vector2 GammaEngine::GraphicSystem::GetBitmapSize(string bitmap)
{
	return render->GetBitmapSize(bitmap);
}
