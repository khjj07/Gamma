#include "stdafx.h"
#include "Time.h"

double Time::deltaTime=0;
Time::Time()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency); 
    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
    timeScale = 1.0 / (double)periodFrequency;
}

Time::~Time()
{

}


void Time::Frame()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    deltaTime = (double)(curTime - lastTime) * timeScale;
    lastTime = curTime;
}