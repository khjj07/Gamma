#include "stdafx.h"

using namespace GammaEngine;

double GammaEngine::Time::deltaTime=0;
GammaEngine::Time::Time()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency); 
    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
    timeScale = 1.0 / (double)periodFrequency;
}

GammaEngine::Time::~Time()
{

}


void GammaEngine::Time::Frame()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    deltaTime = (double)(curTime - lastTime) * timeScale;
    lastTime = curTime;
}