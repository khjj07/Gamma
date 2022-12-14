#include "stdafx.h"

vector<TimerHandler*> Timer::timerHandlerList;
vector<TimerHandler*>::iterator Timer::iter;

Timer::Timer()
{

}

Timer::~Timer()
{

}

TimerHandler* Timer::Delay(float delay, bool loop, function<void()> callback)
{
	TimerHandler* newHandler =new TimerHandler(delay, loop, callback);
	timerHandlerList.push_back(newHandler);
	return newHandler;
}

void Timer::Cancel(TimerHandler* handler)
{
	handler->timeOut = true;
}

void Timer::Frame()
{
	timerHandlerList.erase(remove_if(timerHandlerList.begin(), timerHandlerList.end(), [](TimerHandler* x) {
	if (x->timeOut)
	{
		delete x;
		return true;
	}
	else
	{
		return false;
	}}), timerHandlerList.end());


	for (iter = timerHandlerList.begin(); iter < timerHandlerList.end(); iter++)
	{
		(*iter)->Frame();
	}
}