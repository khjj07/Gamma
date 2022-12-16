#include "stdafx.h"
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")

GraphicSystem::GraphicSystem()
{

}

GraphicSystem::~GraphicSystem()
{
	
}

HRESULT GraphicSystem::Initialize(HWND hWnd)
{
	Screen* screen = Screen::Instance();
	if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory))
	{
		if (S_OK == factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(hWnd, SizeU(screen->width, screen->height)), &renderTarget))
		{
			
		}
		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			CreateTextFormat(string("Verdana"), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30);
		}
	}
	return 0;
}

void GraphicSystem::CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize) {
	IDWriteTextFormat* result;
	writeFactory->CreateTextFormat(ToTCHAR(fontFamilyName), NULL,fontWeight, fontStyle, fontStretch, fontSize, L"", &result);
	textFormatList.push_back(result);
}

void  GraphicSystem::Render()
{
	renderTarget->BeginDraw();
	renderTarget->Clear(ColorF(1, 1, 1));
	 
	vector<Renderer*> renderList = renderComponentList;
	sort(renderList.begin(), renderList.end(), [](Renderer* a, Renderer* b) {
		return a->order < b->order;
	});

	for(renderComponentIter = renderList.begin(); renderComponentIter < renderList.end(); renderComponentIter++)
	{
		(*renderComponentIter)->Render();
		D2D1_POINT_2F center = { 0,0 };
		renderTarget->SetTransform(Matrix3x2F::Rotation(0, center));
	}

	renderTarget->EndDraw();
}

void  GraphicSystem::Release()
{
	vector<IDWriteTextFormat*>::iterator iter;
	for (iter = textFormatList.begin(); iter < textFormatList.end(); iter++)
	{
		(*iter)->Release();
	}

	renderTarget->Release();
	writeFactory->Release();
	factory->Release();
}