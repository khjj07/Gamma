#pragma once
#include <windows.h>
#include "Type.h"

class RenderModule
{
public:
	virtual HRESULT Initialize(HWND hWnd) abstract;
	virtual void Release() abstract;
	virtual void BeginDraw() abstract;
	virtual void EndDraw() abstract;
public:
	virtual void DrawRectangle(vector2 pos, vector2 size,float rotation, Metrerial* meterial);
};

class Metrerial {
// 	ID2D1Brush* pen = 0;
// 	ID2D1Brush* brush = 0;
public:
	vector4 pen;
	vector4 brush;

};