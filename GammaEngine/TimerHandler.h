#pragma once
#include <functional>
using namespace std;
class TimerHandler
{
public:
	TimerHandler();
	TimerHandler(float, bool, function<void()>);
	~TimerHandler();
public:
	void Frame();
public:
	float accumulation = 0;
	float delay = 0;
	bool timeOut = false;
	bool loop;
	function<void()> callback;
private:

};

