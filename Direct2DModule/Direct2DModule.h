#pragma once

class Direct2DModule
{
public:
	Direct2DModule();
	~Direct2DModule();

public:
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//새로운 폰트를 생성하는 함수

public:
	ID2D1Factory* factory = 0;
	ID2D1HwndRenderTarget* renderTarget = 0;
	IDWriteFactory* writeFactory = 0;
	vector<IDWriteTextFormat*> textFormatList;

};

Direct2DModule::Direct2DModule()
{
}

Direct2DModule::~Direct2DModule()
{
}