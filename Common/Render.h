#pragma once
#include <windows.h>
#include <string>
#include "Type.h"
#include <unordered_map>

using namespace std;

class Material {

public:
	vector4 pen;
	vector4 brush;

public:
	Material(): pen(vector4(0, 0, 0, 1)), brush(vector4(0, 0, 0, 0))
	{

	};

	Material(vector4 pen) : pen(pen), brush(vector4(0, 0, 0, 0))
	{

	};

	Material(vector4 pen, vector4 brush) : pen(pen), brush(brush)
	{

	};

};

class RenderModule
{
public:
	virtual HRESULT Initialize(HWND hWnd) abstract;
	virtual void Release() abstract;
	virtual void BeginDraw() abstract;
	virtual void EndDraw() abstract;
public:
	virtual void Resize(int, int) abstract;
	virtual void DrawRectangle(vector2 pos, vector2 size, float rotation, Material* meterial) abstract;
	virtual void DrawEllipse(vector2 pos, vector2 size, float rotation, Material* meterial) abstract;
	virtual void DrawLine(vector2 start, vector2 end, float thickness, Material* meterial) abstract;
	virtual void DrawTextBox(vector2 pos, vector2 size, wstring text, wstring fontFamily, Material* meterial) abstract;
	virtual void DrawBitmap(wstring bitmap, vector2 pos, vector2 size, float rotation, Material* meterial)abstract;
	virtual wstring LoadBitmapImage(wstring) abstract;
	virtual vector2 GetBitmapSize(wstring) abstract;
};
