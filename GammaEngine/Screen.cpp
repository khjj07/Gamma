#include "stdafx.h"
#include "Screen.h"

int Screen::width = 1920;
int Screen::height = 1080;

Screen::Screen()
{

}

Screen::Screen(int w, int h)
{
	width = w;
	height = h;
}

Screen::~Screen()
{

}

void Screen::SetSize(int w, int h)
{
	width = w;
	height = h;
}