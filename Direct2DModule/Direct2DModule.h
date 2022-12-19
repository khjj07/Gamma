#pragma once
#include <string>
using namespace std;
class Render;

class Direct2DModule : public RenderModule
{
public:
	Direct2DModule();
	~Direct2DModule();

public:
	virtual HRESULT Initialize(HWND hWnd);
	virtual void Release();
	virtual void BeginDraw();
	virtual void EndDraw();
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//새로운 폰트를 생성하는 함수
	virtual void DrawRectangle(vector2 pos, vector2 size, float rotation, Metrerial* meterial);
public:
	ID2D1Factory* factory = 0;
	static ID2D1HwndRenderTarget* renderTarget = 0;
	IDWriteFactory* writeFactory = 0;
	vector<IDWriteTextFormat*> textFormatList;
};

