/*
    timer.cpp
*/

#include "timer.h"

#include <iostream>
#include <process.h>             
using namespace std;

#define TIME_COUNT 10

void Timer::Run(){
	
	set_run_flag(true);
	HANDLE handle;
	unsigned uiThreadID;
	handle = (HANDLE)_beginthreadex(NULL,NULL,time_count,this,0,&uiThreadID);
	WaitForSingleObject(handle,0);
	CloseHandle(handle);
}

bool Timer::get_run_flag(){
	return Is_run;
}

void Timer::set_run_flag(bool flag){
	Is_run = flag;
}

unsigned __stdcall time_count(void* pThis){
	
	Timer* timer = (Timer*)pThis;

	if(timer->get_run_flag() == true){
		for(int i=0;i < TIME_COUNT;i++){
			//cout<<"* * *"<<i+1<<"* * *"<<endl;
			Sleep(1000);
		}

		timer->set_run_flag(false);
	}
		
	

	return 0;
}

