#pragma once
#include <windows.h>
#include <string>
#include "Type.h"
#include <unordered_map>

using namespace std;

class Meterial {
public:
	vector4 pen = vector4(0,0,0,1);
	vector4 brush = vector4(0, 0, 0, 0);
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
	virtual void DrawBitmap(string bitmap, vector2 pos, vector2 size, float rotation, Meterial* meterial)abstract;
	virtual string LoadBitmapImage(string) abstract;
	virtual vector2 GetBitmapSize(string) abstract;
	virtual void AddPen(vector4);
	virtual void AddBrush(vector4);
};
