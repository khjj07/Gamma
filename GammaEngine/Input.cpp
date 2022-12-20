#include "stdafx.h"

int Input::mouse[3] = {1,2,4};
KeyState Input::key[256] = { KeyState::none, };
HWND Input::hWnd = NULL;
short Input::mouseScrollDelta = 0;

Input::Input()
{
	
}

Input::~Input()
{

}

void Input::Initialize(HWND hwnd)
{
	hWnd = hwnd;
}

void Input::Frame()
{
	mouseScrollDelta = (short)0;
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i) && key[i] == KeyState::none)
			key[i] = KeyState::pressed;
		else if(GetAsyncKeyState(i) && key[i]==KeyState::pressed)
			key[i] = KeyState::pressing;
		else if(!GetAsyncKeyState(i) && key[i] == KeyState::pressing)
			key[i] = KeyState::released;
		else if(!GetAsyncKeyState(i) && key[i] == KeyState::released)
			key[i] = KeyState::none;
	}
}

bool Input::GetKey(int k)
{
	if (GetAsyncKeyState(k) && key[k] == KeyState::pressing)
	{
		return true;
	}
	return false;
}

bool Input::GetKeyDown(int k)
{
	if (GetAsyncKeyState(k) && key[k] == KeyState::pressed)
	{
		return true;
	}
	return false;
}

bool Input::GetKeyUp(int k)
{
	if (key[k] == KeyState::released)
	{
		return true;
	}
	return false;
}

bool Input::GetMouseButton(int k)
{
	if (GetAsyncKeyState(mouse[k]) && key[mouse[k]] == KeyState::pressing)
	{
		return true;
	}
	return false;
}

bool Input::GetMouseButtonDown(int k)
{
	if (GetAsyncKeyState(mouse[k]) && key[mouse[k]] == KeyState::pressed)
	{
		return true;
	}
	return false;
}

bool Input::GetMouseButtonUp(int k)
{
	if (key[mouse[k]] == KeyState::released)
	{
		return true;
	}
	return false;
}

vector2 Input::GetMousePosition()
{
	RECT rc;
	POINT p;
	GetWindowRect(hWnd, &rc);
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	vector2 vec = vector2(-rc.left+p.x, -rc.top+p.y);
	return vec;
}
