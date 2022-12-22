#include "stdafx.h"
#include "Screen.h"
using namespace GammaEngine;
int Screen::width = 1920;
int Screen::height = 1080;

GammaEngine::Screen::Screen()
{

}

GammaEngine::Screen::Screen(int w, int h)
{
	width = w;
	height = h;
}

GammaEngine::Screen::~Screen()
{

}

void GammaEngine::Screen::SetSize(int w, int h)
{
	width = w;
	height = h;
}