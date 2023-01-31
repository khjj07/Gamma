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
	float thickness;
public:
	Material(): pen(vector4(0, 0, 0, 1)), brush(vector4(0, 0, 0, 0)), thickness(1.f)
	{

	};

	Material(vector4 pen) : pen(pen), brush(vector4(0, 0, 0, 0)), thickness(1.f)
	{

	};

	Material(vector4 pen, vector4 brush, float thickness) : pen(pen), brush(brush), thickness(thickness)
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
	virtual void DrawRectangle(vector2 size, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawPolygon(wstring name, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawEllipse(vector2 size, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawLine(vector2 start, vector2 end, Material* material) abstract;
	virtual void DrawTextBox(vector2 size, Matrix3x3 matrix, wstring text, wstring fontFamily, Material* material) abstract;
	virtual void DrawBitmap(wstring bitmap, vector2 size, Matrix3x3 matrix, Material* material) abstract;
	virtual void DrawBitmap(wstring bitmap, vector2 size, vector2 offset, Matrix3x3 matrix, Material* material) abstract;
	virtual wstring LoadBitmapImage(wstring) abstract;
	virtual wstring MakePolygon(wstring,vector<vector2>) abstract;
	virtual vector2 GetBitmapSize(wstring) abstract;
};
