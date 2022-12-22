#pragma once
#include <vector>


using namespace std;
namespace GammaEngine
{
	class TimerHandler;

	/// <summary>
	/// Ÿ�̸Ӹ� ���� ���� �����ϴ� Ŭ����
	/// </summary>
	class GammaEngineAPI Timer : public Singleton<Timer>
	{
	public:
		Timer();
		~Timer();

	public:
		void Frame();

	public:
		static TimerHandler* Delay(float delay, bool loop, function<void()> callback);//���� ������ ���Ŀ� Callback�Լ��� ȣ���ϴ� Ÿ�̸Ӹ� ����
		static void Cancel(TimerHandler* handler);//Ÿ�̸Ӹ� �����ϴ� �Լ�

	public:
		static vector<TimerHandler*> timerHandlerList;
		static vector<TimerHandler*>::iterator iter;
	};

}
