#pragma once
class Time : public Singleton<Time>
{
public:
	Time();
	~Time();
	void Frame();
public:
	static double deltaTime; //������ ������ �ð� Time.deltaTime���� ȣ��
private:
	__int64 periodFrequency;
	__int64 curTime;
	__int64 lastTime;
	double timeScale;
};