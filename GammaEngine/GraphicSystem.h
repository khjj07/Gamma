#pragma once
#include <vector>

using namespace std;

class Renderer;

/// <summary>
/// Direct2D�� �⺻���� ����� �����ϴ� class
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
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//���ο� ��Ʈ�� �����ϴ� �Լ�

public:
	vector<Renderer*> renderComponentList;
	vector<Renderer*>::iterator renderComponentIter;
	vector<IDWriteTextFormat*> textFormatList;
};

