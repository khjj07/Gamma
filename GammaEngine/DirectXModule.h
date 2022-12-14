#pragma once
#include <vector>

using namespace std;

class Renderer;

/// <summary>
/// Direct2D�� �⺻���� ����� �����ϴ� class
/// </summary>
class DirectXModule : public Singleton<DirectXModule>
{
public:
	DirectXModule();
	~DirectXModule();

public:
	HRESULT Initialize(HWND);
	void Render();
	void Release();

public:
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//���ο� ��Ʈ�� �����ϴ� �Լ�

public:
	ID2D1Factory* factory = 0;
	ID2D1HwndRenderTarget* renderTarget = 0;
	IDWriteFactory* writeFactory = 0;
	vector<Renderer*> renderComponentList;
	vector<Renderer*>::iterator renderComponentIter;
	vector<IDWriteTextFormat*> textFormatList;
};

