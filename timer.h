/*
 *   本段代码实现了一个定时器的功能。
 *   包含 registerHandler、setInterval、setStopFlag三个功能
 *   
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "Thread.h"

class Timer :public Thread
{
	typedef void(CALLBACK *Timerfunc)(void* p);
	typedef Timerfunc TimerHandler;
public:
	Timer()
		:m_handler(0)
		, m_interval(-1)
	{

	}

	/* 设定定时时间到调用的函数handler,传入的参数p 
	 * handler对应函数的地址，函数类型为void CALLBACK
	 * p可以使int*型或者void*型
	 */
	void registerHandler(TimerHandler handler, void* p)
	{
		m_handler = handler;
		m_parameter = p;
	}

	/* 设定定时器调用回调函数的时间间隔，即每隔millsecond毫秒
	 * 调用一次回调函数
	 */
	void setInterval(int millisecond)
	{
		m_interval = millisecond;
	}

	/* 运行计时函数，开始计时 */
	void Run()
	{
		unsigned long tickNow = ::GetTickCount();
		unsigned long tickLastTime = tickNow;

		while (!IsStop())
		{
			tickNow = ::GetTickCount();
			if (tickNow - tickLastTime > m_interval)
			{
				if (m_handler)
				{
					(*m_handler)(m_parameter);
				}
				tickLastTime = ::GetTickCount();
			}

			::Sleep(1);
		}
	}

	/* 停止计时 */
	void Cancel()
	{
		Stop();
	}

	/* 重启计时器*/
	void setStopFlag(){
		Set_StopFlag();
	}

private:
	TimerHandler  m_handler;
	int           m_interval;
	void*         m_parameter;
};

#endif