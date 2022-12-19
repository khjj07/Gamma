#pragma once
#include <windows.h>
#include <string>
#include "Type.h"

using namespace std;

class Meterial {
// 	ID2D1Brush* pen = 0;
// 	ID2D1Brush* brush = 0;
public:
	vector4 pen;
	vector4 brush;
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
	virtual void DrawRectangle(vector2 pos, vector2 size, float rotation, Meterial* meterial) abstract;
	virtual void DrawEllipse(vector2 pos, vector2 size, float rotation, Meterial* meterial) abstract;
	virtual void DrawLine(vector2 start, vector2 end, float thickness, Meterial* meterial) abstract;
	virtual void DrawTextBox(vector2 pos, vector2 size, string text, Meterial* meterial) abstract;
};