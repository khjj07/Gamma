#pragma once
#include <string>
#include <d3d9.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#ifdef Direct2DModuleAPI_Exporting
#define Direct2DModuleAPI __declspec(dllexport)
#else
#define Direct2DModuleAPI __declspec(dllimport)
#endif

using namespace std;
using namespace D2D1;
class RenderModule;

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
	void CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize);//새로운 폰트를 생성하는 함수
	virtual void Resize(int, int);
	virtual void DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial);
	virtual void DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial);
	virtual void DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial);
	virtual void DrawTextBox(vector2 pos, vector2 size, string text, Meterial* meterial);
	virtual void DrawBitmap(string bitmap, vector2 pos, vector2 size, float rotation, Meterial* meterial);
	virtual string LoadBitmapImage(string filename);
	virtual vector2 GetBitmapSize(string filename);
	virtual void AddPen(vector4);
	virtual void AddBrush(vector4);
	ID2D1SolidColorBrush* UsePen(vector4);
	ID2D1SolidColorBrush* UseBrush(vector4);

public:
	ID2D1Factory* factory;
	IDWriteFactory* writeFactory;
	IWICImagingFactory* imageFactory;
	static ID2D1HwndRenderTarget* renderTarget;
public:
	vector<IDWriteTextFormat*> textFormatList;
	unordered_map<string, ID2D1Bitmap*> bitmapDictionary;
	unordered_map<vector4, ID2D1SolidColorBrush*> penDictionary;
	unordered_map<vector4, ID2D1SolidColorBrush*> brushDictionary;
};

