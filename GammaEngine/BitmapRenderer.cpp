#include "stdafx.h"
#pragma comment (lib, "windowscodecs.lib")

BitmapRenderer::BitmapRenderer() :Renderer()
{

}

BitmapRenderer::BitmapRenderer(GameObject* t) :Renderer(t)
{
	
}

BitmapRenderer::~BitmapRenderer()
{

}

int BitmapRenderer::LoadBitmapImage(string filename)
{
    size = vector2(100, 100);
    HRESULT hr;

    // ���ڴ� ����

    IWICBitmapDecoder* decoder = 0;

    hr = factory->CreateDecoderFromFilename(ToTCHAR(filename), 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

    if (FAILED(hr))
        return hr;



    // ������ ���

    IWICBitmapFrameDecode* frameDecode = 0;

    // 0�� �������� �о����.

    hr = decoder->GetFrame(0, &frameDecode);

    if (FAILED(hr))

    {

        decoder->Release();

        return hr;

    }



    // ������ ����

    IWICFormatConverter* converter = 0;

    hr = factory->CreateFormatConverter(&converter);

    if (FAILED(hr))

    {

        decoder->Release();

        return hr;

    }



    // ������ �ʱ�ȭ

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

        return hr;

    }



    // WIC ��Ʈ�����κ��� D2D ��Ʈ�� ����

    hr = renderTarget->CreateBitmapFromWicBitmap(converter, 0, &bitmap);


    // �ڿ� ����
    size.x = bitmap->GetSize().width;
    size.y = bitmap->GetSize().height;
    decoder->Release();

    frameDecode->Release();

    converter->Release();


    return hr;
}

void BitmapRenderer::Render()
{

    vector2 renderPos = transform->position + offset;
    vector2 renderSize = size;
    renderSize.x = renderSize.x * transform->scale.x;
    renderSize.y = renderSize.y * transform->scale.y;
    Renderer::Adjust(renderPos, renderSize);
    D2D1_RECT_F rectangle;
    D2D1_POINT_2F center = { renderPos.x,  renderPos.y };
    rectangle.left = renderPos.x - renderSize.x / 2;
    rectangle.top = renderPos.y - renderSize.y / 2;
    rectangle.right = renderPos.x + renderSize.x / 2;
    rectangle.bottom = renderPos.y + renderSize.y / 2;
    renderTarget->SetTransform(Matrix3x2F::Rotation(transform->rotation, center));
    renderTarget->DrawBitmap(bitmap, rectangle,1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
   
}