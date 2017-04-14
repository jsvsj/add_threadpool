#ifndef _WORK_THREAD_H
#define _WORK_THREAD_H

#include"Mutex.h"
#include"Thread.h"
#include"Condition.h"
#include<deque>

class Addthreadpool;
class Task;

using namespace std;


class WorkThread:public Thread
{
private:
	int thread_id_;
	Addthreadpool *pool_;
	deque<Task *> task_queue_;
	
	Mutex mutex_;
	Condition cond_;
	
public:
	void addTask(Task * task);
	Task* getTask();
	
	WorkThread(int thread_id,Addthreadpool *pool);
	~WorkThread();
	virtual void run();	
	
};




#endif