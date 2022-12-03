#pragma once
class Time : public Singleton<Time>
{
public:
	Time();
	~Time();
	void Frame();
public:
	static double deltaTime; //프레임 사이의 시간 Time.deltaTime으로 호출
private:
	__int64 periodFrequency;
	__int64 curTime;
	__int64 lastTime;
	double timeScale;
};