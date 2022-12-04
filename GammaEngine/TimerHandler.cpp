#include "stdafx.h"

TimerHandler::TimerHandler()
{

}

TimerHandler::~TimerHandler()
{

}

TimerHandler::TimerHandler(float d, bool l, function<void()> c)
{
	delay = d;
	loop = l;
	callback = c;
}

void TimerHandler::Frame()
{
	accumulation += Time::deltaTime;
	if (!timeOut && delay <= accumulation)
	{
		callback();
		if (!loop)
		{
			Timer::Cancel(this);
		}
		else
		{
			accumulation = 0;
		}
	}
}