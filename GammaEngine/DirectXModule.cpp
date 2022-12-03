#include "stdafx.h"
#include "DirectXModule.h"
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")

DirectXModule::DirectXModule()
{

}

DirectXModule::~DirectXModule()
{
	
}

HRESULT DirectXModule::Initialize(HWND hWnd)
{
	Screen* screen = Screen::Instance();
	if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory))
	{
		if (S_OK == factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(hWnd, SizeU(screen->width, screen->height)), &renderTarget))
		{
			
		}
		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			CreateTextFormat(string("Verdana"), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20);
		}
	}
	return 0;
}

void DirectXModule::CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize) {
	IDWriteTextFormat* result;
	writeFactory->CreateTextFormat(ToTCHAR(fontFamilyName), NULL,fontWeight, fontStyle, fontStretch, fontSize, L"", &result);
	textFormatList.push_back(result);
}

void  DirectXModule::Render()
{
	renderTarget->BeginDraw();
	renderTarget->Clear(ColorF(1, 1, 1));
	 

	for(renderComponentIter = renderComponentList.begin(); renderComponentIter < renderComponentList.end(); renderComponentIter++)
	{
		(*renderComponentIter)->Render();
	}
	renderTarget->EndDraw();
}

void  DirectXModule::Release()
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