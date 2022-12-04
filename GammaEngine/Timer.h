#pragma once
#include <functional>
#include <vector>
using namespace std;
class TimerHandler;
class Timer : public Singleton<Timer>
{
public:
	Timer();
	~Timer();
public:
	static TimerHandler* Delay(float, bool, function<void()>);
	static void Cancel(TimerHandler*);
	void Frame();
public:
	static vector<TimerHandler*> timerHandlerList;
	static vector<TimerHandler*>::iterator iter;
private:

};
