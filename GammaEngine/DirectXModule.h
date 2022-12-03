#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class Renderer;
class DirectXModule : public Singleton<DirectXModule>
{
public:
	DirectXModule();
	~DirectXModule();
public:
	HRESULT Initialize(HWND);
	void Render();
	void Release();
	void DirectXModule::CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);
public:
	ID2D1Factory* factory = 0;
	ID2D1HwndRenderTarget* renderTarget = 0;
	IDWriteFactory* writeFactory = 0;
	vector<Renderer*> renderComponentList;
	vector<Renderer*>::iterator renderComponentIter;
	vector<IDWriteTextFormat*> textFormatList;
private:

};

