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
#if DEBUG
	Debug::Render();
#endif
	render->EndDraw();
}

void GammaEngine::GraphicSystem::Resize(int width, int height)
{
	render->Resize(width, height);
}

void GammaEngine::GraphicSystem::DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material)
{
	render->DrawRectangle(size, matrix, material);
}


void GammaEngine::GraphicSystem::DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material)
{
	render->DrawEllipse(size, matrix, material);
}

void GammaEngine::GraphicSystem::DrawLine(vector2 start, vector2 end, Material* material)
{
	render->DrawLine(start, end, material);
}

void GammaEngine::GraphicSystem::DrawTextBox(vector2 size, Matrix3x3 matrix, wstring text, wstring fontFamily, Material* material)
{
	render->DrawTextBox(size, matrix,text, fontFamily, material);
}

void GammaEngine::GraphicSystem::DrawBitmap(wstring bitmap, vector2 size, Matrix3x3 matrix, Material* meterial)
{
	render->DrawBitmap(bitmap, size, matrix, meterial);
}

void GammaEngine::GraphicSystem::DrawPolygon(wstring name, Matrix3x3 matrix, Material* material)
{
	render->DrawPolygon(name, matrix, material);
}

wstring GammaEngine::GraphicSystem::LoadBitmapImage(wstring filename)
{
	return render->LoadBitmapImage(filename);
}

vector2 GammaEngine::GraphicSystem::GetBitmapSize(wstring bitmap)
{
	return render->GetBitmapSize(bitmap);
}

wstring GammaEngine::GraphicSystem::MakePolygon(wstring name, vector<vector2> points)
{
	return render->MakePolygon(name, points);
}