

#include "Direct2DModule.h"

#include "Util.h"

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace D2D1;

ID2D1HwndRenderTarget* Direct2DModule::renderTarget = 0;

Direct2DModule::Direct2DModule()
{
	factory = 0;
	writeFactory = 0;
	imageFactory = 0;
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
		if (S_OK == factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(hWnd, SizeU(rect.right - rect.left, rect.bottom - rect.top)), &renderTarget))
		{

		}
		if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)))
		{
			wstring font =(L"Verdana");
			CreateTextFormat(font, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30);
		}
		if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory)))
		{

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

void Direct2DModule::CreateTextFormat(wstring fontFamilyName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, int fontSize) 
{
	IDWriteTextFormat* result;
	
	writeFactory->CreateTextFormat(fontFamilyName.c_str(), NULL, fontWeight, fontStyle, fontStretch, fontSize, L"", &result);
	textFormatDictionary.insert(make_pair(fontFamilyName, result));
}

void Direct2DModule::Release()
{
	for (auto textFormat : textFormatDictionary)
	{
		textFormat.second->Release();
	}

	for (auto bitmap : bitmapDictionary)
	{
		bitmap.second->Release();
	}

	for (auto brush : brushDictionary)
	{
		brush.second->Release();
	}
	textFormatDictionary.clear();
	brushDictionary.clear();
	bitmapDictionary.clear();
	renderTarget->Release();
	writeFactory->Release();
	imageFactory->Release();
	factory->Release();
}

void Direct2DModule::Resize(int width, int height)
{
	renderTarget->Resize(SizeU(width, height));
}

wstring Direct2DModule::LoadBitmapImage(wstring filename)
{
	HRESULT hr;
	ID2D1Bitmap* bitmap;
	IWICBitmapDecoder* decoder = 0;

	hr = imageFactory->CreateDecoderFromFilename(filename.c_str(), 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

	if (FAILED(hr))
		return nullptr;
	IWICBitmapFrameDecode* frameDecode = 0;

	hr = decoder->GetFrame(0, &frameDecode);

	if (FAILED(hr))
	{

		decoder->Release();

		return nullptr;

	}

	IWICFormatConverter* converter = 0;

	hr = imageFactory->CreateFormatConverter(&converter);

	if (FAILED(hr))
	{
		decoder->Release();
		return nullptr;
	}

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


	hr = renderTarget->CreateBitmapFromWicBitmap(converter, 0, &bitmap);

	bitmapDictionary.insert(make_pair(filename, bitmap));

	decoder->Release();
	frameDecode->Release();
	converter->Release();

	return filename;
}

void Direct2DModule::AddBrush(vector4 color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(ColorF(color.x, color.y, color.z, color.w), (ID2D1SolidColorBrush**)&brush);
	brushDictionary.insert(make_pair(color, brush));
}

ID2D1SolidColorBrush* Direct2DModule::UseBrush(vector4 color)
{
	if (brushDictionary.find(color) == brushDictionary.end())
	{
		AddBrush(color);
	}
	ID2D1SolidColorBrush* brush = brushDictionary[color];
	return brush;
}


vector2 Direct2DModule::GetBitmapSize(wstring filename)
{
	ID2D1Bitmap* bitmap = bitmapDictionary[filename];
	D2D1_SIZE_F size = bitmap->GetSize();
	return vector2(size.width, size.height);
}

void Direct2DModule::DrawRectangle(vector2 size, vector2 pos, vector2 scale, float rotation, Material* material)
{
	D2D1_RECT_F rectangle;
	D2D1_POINT_2F center = { pos.x,  pos.y };
	D2D1_SIZE_F _scale = { scale.x,scale.y };
	rectangle.left = -size.x / 2;
	rectangle.top = -size.y / 2;
	rectangle.right = size.x / 2;
	rectangle.bottom = size.y / 2;

	renderTarget->SetTransform(Matrix3x2F::Translation(pos.x, pos.y)* Matrix3x2F::Scale(_scale, center)* Matrix3x2F::Rotation(rotation, center));

	renderTarget->DrawRectangle(rectangle, UseBrush(material->pen));
	renderTarget->FillRectangle(rectangle, UseBrush(material->brush));

	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
	renderTarget->SetTransform(Matrix3x2F::Translation(0, 0));
}
wstring Direct2DModule::MakePolygon(wstring name, vector<vector2> points)
{
	ID2D1PathGeometry* polygon;
	ID2D1GeometrySink* pSink = NULL;
	HRESULT hr = factory->CreatePathGeometry(&polygon);
	vector<D2D1_POINT_2F> p;
	for (auto iter = points.begin(); iter != points.end(); iter++)
	{
		p.push_back({ (*iter).x,(*iter).y });
	}

	if (SUCCEEDED(hr))
	{
		hr = polygon->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->BeginFigure(
				p[0],
				D2D1_FIGURE_BEGIN_FILLED
			);
			for (int i = 1; i < p.size(); i++)
			{
				pSink->AddLine(p[i]);
			}
			
			pSink->AddLine(p[0]);

			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

			hr = pSink->Close();
		}
		pSink->Release();
		polygonDictionary.insert(make_pair(name ,polygon));
	}
	return name;
}
void Direct2DModule::DrawPolygon(wstring name, vector2 pos,vector2 scale, float rotation, Material* material)
{
	D2D1_POINT_2F center = { pos.x,  pos.y };
	D2D1_SIZE_F _scale = { scale.x,scale.y };

	renderTarget->SetTransform(Matrix3x2F::Translation(pos.x, pos.y) * Matrix3x2F::Scale(_scale, center) * Matrix3x2F::Rotation(rotation, center));

	renderTarget->DrawGeometry(polygonDictionary[name], UseBrush(material->pen), 1.f);
	renderTarget->FillGeometry(polygonDictionary[name], UseBrush(material->brush));

	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
}

void Direct2DModule::DrawEllipse(vector2 size, vector2 pos, vector2 scale, float rotation, Material* material)
{
	D2D1_ELLIPSE ellipse;

	ellipse.radiusX = size.x / 2;
	ellipse.radiusY = size.y / 2;
	ellipse.point.x =0;
	ellipse.point.y =0;

	D2D1_POINT_2F center = { pos.x,  pos.y };
	D2D1_SIZE_F _scale = { scale.x,scale.y };

	renderTarget->SetTransform(Matrix3x2F::Translation(pos.x, pos.y) * Matrix3x2F::Scale(_scale, center) * Matrix3x2F::Rotation(rotation, center));


	renderTarget->DrawEllipse(ellipse, UseBrush(material->pen));
	renderTarget->FillEllipse(ellipse, UseBrush(material->brush));
	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
}

void Direct2DModule::DrawLine(vector2 start, vector2 end, Material* material)
{
	renderTarget->DrawLine(
		Point2F(start.x, start.y),
		Point2F(end.x, end.y),
		UseBrush(material->pen),
		material->thickness,
		nullptr
	);
}

void Direct2DModule::DrawTextBox(vector2 size, vector2 pos, vector2 scale, wstring text, wstring fontFamily, Material* material)
{
	renderTarget->DrawText(text.c_str(), text.length() - 1, textFormatDictionary[fontFamily], RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y), UseBrush(material->pen));
}

void Direct2DModule::DrawBitmap(wstring bitmap, vector2 size, vector2 pos, vector2 scale, float rotation, Material* material)
{
	D2D1_RECT_F rectangle;
	D2D1_POINT_2F center = { pos.x,  pos.y };
	D2D1_SIZE_F _scale = { scale.x,scale.y };

	rectangle.left = -size.x / 2;
	rectangle.top = -size.y / 2;
	rectangle.right = size.x / 2;
	rectangle.bottom = size.y / 2;

	renderTarget->SetTransform(Matrix3x2F::Translation(pos.x, pos.y) * Matrix3x2F::Scale(_scale, center) * Matrix3x2F::Rotation(rotation, center));

	renderTarget->DrawBitmap(bitmapDictionary[bitmap], rectangle, material->brush.w, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	D2D1_POINT_2F centerz = { 0,0 };
	renderTarget->SetTransform(Matrix3x2F::Rotation(0, centerz));
}