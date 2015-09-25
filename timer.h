#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>



class Timer{
public:
	Timer(){
		Is_run = false;
	}

	bool get_run_flag();
	void set_run_flag(bool flag);

	void Run();
private:
	
	
	bool Is_run;
};

unsigned __stdcall time_count(void* pThis);

#endif