#pragma once
#include <windows.h>
#include <vector>
#include <string>
//#include <d3d9.h>
//#include <d2d1_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Type.h"
#include "Render.h"

#if Direct2DModuleAPI_Exporting
#define Direct2DModuleAPI __declspec(dllexport)
#else
#define Direct2DModuleAPI __declspec(dllimport)
#endif

using namespace std;
using namespace D2D1;

class Direct2DModuleAPI Direct2DModule : public RenderModule
{
public:
	Direct2DModule();
	~Direct2DModule();

public:
	virtual HRESULT Initialize(HWND hWnd);
	virtual void Release();
	virtual void BeginDraw();
	virtual void EndDraw();
	void CreateTextFormat(wstring fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//���ο� ��Ʈ�� �����ϴ� �Լ�
	virtual void Resize(int, int);
	virtual void DrawRectangle(vector2 pos, vector2 size, float rotation, Material* meterial);
	virtual void DrawEllipse(vector2 pos, vector2 size, float rotation, Material* meterial);
	virtual void DrawLine(vector2 start, vector2 end, float thickness, Material* meterial);
	virtual void DrawTextBox(vector2 pos, vector2 size, wstring text, wstring fontFamily, Material* meterial);
	virtual void DrawBitmap(wstring bitmap, vector2 pos, vector2 size, float rotation, Material* meterial);
	virtual wstring LoadBitmapImage(wstring filename);
	virtual vector2 GetBitmapSize(wstring filename);
	void AddBrush(vector4);
	ID2D1SolidColorBrush* UseBrush(vector4);

public:
	ID2D1Factory* factory;
	IDWriteFactory* writeFactory;
	IWICImagingFactory* imageFactory;
	static ID2D1HwndRenderTarget* renderTarget;
public:
	unordered_map<wstring, IDWriteTextFormat*> textFormatDictionary;
	unordered_map<wstring, ID2D1Bitmap*> bitmapDictionary;
	unordered_map<vector4, ID2D1SolidColorBrush*> brushDictionary;
};

