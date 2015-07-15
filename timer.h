/*
 *   ���δ���ʵ����һ����ʱ���Ĺ��ܡ�
 *   ���� registerHandler��setInterval��setStopFlag��������
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

	/* �趨��ʱʱ�䵽���õĺ���handler,����Ĳ���p 
	 * handler��Ӧ�����ĵ�ַ����������Ϊvoid CALLBACK
	 * p����ʹint*�ͻ���void*��
	 */
	void registerHandler(TimerHandler handler, void* p)
	{
		m_handler = handler;
		m_parameter = p;
	}

	/* �趨��ʱ�����ûص�������ʱ��������ÿ��millsecond����
	 * ����һ�λص�����
	 */
	void setInterval(int millisecond)
	{
		m_interval = millisecond;
	}

	/* ���м�ʱ��������ʼ��ʱ */
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

	/* ֹͣ��ʱ */
	void Cancel()
	{
		Stop();
	}

	/* ������ʱ��*/
	void setStopFlag(){
		Set_StopFlag();
	}

private:
	TimerHandler  m_handler;
	int           m_interval;
	void*         m_parameter;
};

#endif