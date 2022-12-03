#include "stdafx.h"
#include "Time.h"

double Time::deltaTime=0;
Time::Time()
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
    //1�ʵ��� CPU�� �������� ��ȯ�ϴ� �Լ� (������. �ý��� ���ý� ������)

    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
    // �������Լ��� Update()�Լ����� ������ ����Ǳ� ������ lastTime�� ����.

    timeScale = 1.0 / (double)periodFrequency;
}

Time::~Time()
{

}


void Time::Frame()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime); // ���� ������ ������ ����.

    deltaTime = (double)(curTime - lastTime) * timeScale; // (���� ������ ������ - ���� ������ ������) * ( 1 / �ʴ������� )

    lastTime = curTime; // ���� �������� ���� ���������� ����. ���� ��� �ݺ�.
}