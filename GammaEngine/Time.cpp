#include "stdafx.h"
#include "Time.h"

double Time::deltaTime=0;
Time::Time()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
    //1초동안 CPU의 진동수를 반환하는 함수 (고정값. 시스템 부팅시 고정됨)

    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
    // 생성자함수는 Update()함수보다 이전에 실행되기 때문에 lastTime에 저장.

    timeScale = 1.0 / (double)periodFrequency;
}

Time::~Time()
{

}


void Time::Frame()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime); // 현재 프레임 진동수 저장.

    deltaTime = (double)(curTime - lastTime) * timeScale; // (현재 프레임 진동수 - 이전 프레임 진동수) * ( 1 / 초당진동수 )

    lastTime = curTime; // 현재 프레임을 이전 프레임으로 저장. 이후 계속 반복.
}