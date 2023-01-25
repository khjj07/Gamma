#include "stdafx.h"
using namespace GammaEngine;
vector<TimerHandler*>* Timer::timerHandlerList;

GammaEngine::Timer::Timer()
{
	timerHandlerList = new vector<TimerHandler*>();
}

GammaEngine::Timer::~Timer()
{

}

TimerHandler* GammaEngine::Timer::Delay(float delay, bool loop, function<void()> callback)
{
	TimerHandler* newHandler =new TimerHandler(delay, loop, callback);
	timerHandlerList->push_back(newHandler);
	return newHandler;
}

void GammaEngine::Timer::Cancel(TimerHandler* handler)
{
	handler->timeOut = true;
}

void GammaEngine::Timer::Frame()
{
	timerHandlerList->erase(remove_if(timerHandlerList->begin(), timerHandlerList->end(), [](TimerHandler* x) {
	if (x->timeOut)
	{
		delete x;
		return true;
	}
	else
	{
		return false;
	}}), timerHandlerList->end());


	for (auto iter = timerHandlerList->begin(); iter < timerHandlerList->end(); iter++)
	{
		(*iter)->Frame();
	}
}