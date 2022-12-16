#pragma once
#include <vector>

using namespace std;

class Renderer;

/// <summary>
/// Direct2D의 기본적인 기능을 포함하는 class
/// </summary>
class GraphicSystem : public Singleton<GraphicSystem>
{
public:
	GraphicSystem();
	~GraphicSystem();

public:
	HRESULT Initialize(HWND);
	void Render();
	void Release();

public:
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//새로운 폰트를 생성하는 함수

public:
	vector<Renderer*> renderComponentList;
	vector<Renderer*>::iterator renderComponentIter;
	vector<IDWriteTextFormat*> textFormatList;
};

