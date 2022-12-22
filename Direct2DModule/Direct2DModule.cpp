
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
	factory=0;
	writeFactory=0;
	imageFactory=0;
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



void Direct2DModule::Release()
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

string Direct2DModule::LoadBitmapImage(string filename)
{
	HRESULT hr;
	ID2D1Bitmap* bitmap;
	// 디코더 생성

	IWICBitmapDecoder* decoder = 0;

	hr = imageFactory->CreateDecoderFromFilename(ToTCHAR(filename), 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
		return nullptr;



	// 프레임 얻기

	IWICBitmapFrameDecode* frameDecode = 0;

	// 0번 프레임을 읽어들임.

	hr = decoder->GetFrame(0, &frameDecode);

	if (FAILED(hr))

	{

		decoder->Release();

		return nullptr;

	}



	// 컨버터 생성

	IWICFormatConverter* converter = 0;

	hr = imageFactory->CreateFormatConverter(&converter);

	if (FAILED(hr))
	{
		decoder->Release();
		return nullptr;
	}

	// 컨버터 초기화
	hr = converter->Initialize(
		frameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		0, 0.0, WICBitmapPaletteTypeCustom
	);

	if (FAILED(hr))
	{
		decoder->Release();
		frameDecode->Release();
		converter->Release();
		return nullptr;
	}


	// WIC 비트맵으로부터 D2D 비트맵 생성
	hr = renderTarget->CreateBitmapFromWicBitmap(converter, 0, &bitmap);
	bitmapDictionary.insert({ filename, bitmap });
	// 자원 해제
	decoder->Release();
	frameDecode->Release();
	converter->Release();

	return filename;
}

void Direct2DModule::AddPen(vector4 color)
{
	ID2D1SolidColorBrush* pen;
	renderTarget->CreateSolidColorBrush(ColorF(color.x, color.y, color.z, color.w), (ID2D1SolidColorBrush**)&pen);
	
	if (penDictionary.find(color) != penDictionary.end())
	{
		penDictionary.insert({ color,pen });
	}
}

ID2D1SolidColorBrush* Direct2DModule::UsePen(vector4 color)
{
	if (penDictionary.find(color) != penDictionary.end())
	{
		AddPen(color);
	}
	return brushDictionary.at(color);
}

void Direct2DModule::AddBrush(vector4 color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(ColorF(color.x, color.y, color.z, color.w), (ID2D1SolidColorBrush**)&brush);

	if (brushDictionary.find(color) != brushDictionary.end())
	{
		brushDictionary.insert({ color,brush });
	}
}

ID2D1SolidColorBrush* Direct2DModule::UseBrush(vector4 color)
{
	if (brushDictionary.find(color) != penDictionary.end())
	{
		AddPen(color);
	}
	return brushDictionary.at(color);
}


vector2 Direct2DModule::GetBitmapSize(string filename)
{
	D2D1_SIZE_F size = bitmapDictionary.at(filename)->GetSize();
	return vector2(size.width, size.height);
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
	
	renderTarget->DrawRectangle(rectangle, pen);
	renderTarget->FillRectangle(rectangle, brush);

	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
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

	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
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

void Direct2DModule::DrawBitmap(string bitmap,vector2 pos, vector2 size, float rotation, Meterial* meterial)
{
	D2D1_RECT_F rectangle;
	D2D1_POINT_2F center = { pos.x,  size.y };
	rectangle.left = pos.x - size.x / 2;
	rectangle.top = pos.y - size.y / 2;
	rectangle.right = pos.x + size.x / 2;
	rectangle.bottom = pos.y + size.y / 2;
	renderTarget->SetTransform(Matrix3x2F::Rotation(rotation, center));
	renderTarget->DrawBitmap(bitmapDictionary.at(bitmap), rectangle, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
}