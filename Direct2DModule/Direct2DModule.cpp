#include <d3d9.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "Render.h"
#include "Util.h"
#include "Direct2DModule.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace D2D1;

ID2D1HwndRenderTarget* Direct2DModule::renderTarget = 0;

Direct2DModule::Direct2DModule()
{

}

Direct2DModule::~Direct2DModule()
{

}

HRESULT Direct2DModule::Initialize(HWND hWnd)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);

	if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory))
	{
		if (S_OK == factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(hWnd, SizeU(rect.right- rect.left, rect.bottom- rect.top)), &renderTarget))
		{

		}
		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			CreateTextFormat(string("Verdana"), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30);
		}
	}
	return 0;
}

void Direct2DModule::BeginDraw()
{
	renderTarget->BeginDraw();
	renderTarget->Clear(ColorF(1, 1, 1));
}

void Direct2DModule::EndDraw()
{
	renderTarget->EndDraw();
}

void Direct2DModule::CreateTextFormat(string fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize) {
	IDWriteTextFormat* result;
	writeFactory->CreateTextFormat(ToTCHAR(fontFamilyName), NULL, fontWeight, fontStyle, fontStretch, fontSize, L"", &result);
	textFormatList.push_back(result);
}



void  Direct2DModule::Release()
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

void Direct2DModule::Resize(int width, int height)
{
	renderTarget->Resize(SizeU(width, height));
}

void Direct2DModule::DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	ID2D1SolidColorBrush* brush;
	ID2D1SolidColorBrush* pen;
	D2D1_RECT_F rectangle;
	D2D1_POINT_2F center = { pos.x,  size.y };

	rectangle.left = pos.x - size.x / 2;
	rectangle.top = pos.y - size.y / 2;
	rectangle.right = pos.x + size.x / 2;
	rectangle.bottom = pos.y + size.y / 2;

	renderTarget->SetTransform(Matrix3x2F::Rotation(rotation, center));
	renderTarget->CreateSolidColorBrush(ColorF(meterial->pen.x, meterial->pen.y, meterial->pen.z, meterial->pen.w), (ID2D1SolidColorBrush**)&pen);
	renderTarget->CreateSolidColorBrush(ColorF(meterial->brush.x, meterial->brush.y, meterial->brush.z, meterial->brush.w), (ID2D1SolidColorBrush**)&brush);
	renderTarget->DrawRectangle(rectangle, pen);
	renderTarget->FillRectangle(rectangle, brush);

	D2D1_POINT_2F center = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, center));
}

void Direct2DModule::DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	ID2D1SolidColorBrush* brush;
	ID2D1SolidColorBrush* pen;
	D2D1_ELLIPSE ellipse;

	ellipse.radiusX = size.x / 2;
	ellipse.radiusY = size.y / 2;
	ellipse.point.x = pos.x;
	ellipse.point.y = pos.y;

	D2D1_POINT_2F center = { pos.x,  pos.y };
	renderTarget->SetTransform(Matrix3x2F::Rotation(rotation, center));
	renderTarget->CreateSolidColorBrush(ColorF(meterial->pen.x, meterial->pen.y, meterial->pen.z, meterial->pen.w), (ID2D1SolidColorBrush**)&pen);
	renderTarget->CreateSolidColorBrush(ColorF(meterial->brush.x, meterial->brush.y, meterial->brush.z, meterial->brush.w), (ID2D1SolidColorBrush**)&brush);
	renderTarget->DrawEllipse(ellipse, pen);
	renderTarget->FillEllipse(ellipse, brush);

	D2D1_POINT_2F center = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, center));
}

void Direct2DModule::DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial)
{
	ID2D1SolidColorBrush* pen;
	renderTarget->CreateSolidColorBrush(ColorF(meterial->pen.x, meterial->pen.y, meterial->pen.z, meterial->pen.w), (ID2D1SolidColorBrush**)&pen);

	renderTarget->DrawLine(
		Point2F(start.x, start.y),
		Point2F(end.x, end.y),
		pen,
		thickness,
		nullptr
	);
}

void Direct2DModule::DrawTextBox(vector2 pos, vector2 size, string text, Meterial* meterial)
{
	TCHAR* str = ToTCHAR(text);

	ID2D1SolidColorBrush* pen;
	renderTarget->CreateSolidColorBrush(ColorF(meterial->pen.x, meterial->pen.y, meterial->pen.z, meterial->pen.w), (ID2D1SolidColorBrush**)&pen);

	renderTarget->DrawText(
		str,
		text.length() - 1,
		textFormatList.at(0),
		RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y),
		pen
	);
}