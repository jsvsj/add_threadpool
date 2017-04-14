#ifndef _POST_THREAD_H_
#define _POST_THREAD_H_
#include"Mutex.h"
#include"Thread.h"
#include"Condition.h"
#include<deque>

class Addthreadpool;
class Task;

using namespace std;


class PostThread:public Thread
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
	
	PostThread(int thread_id,Addthreadpool *pool);
	~PostThread();
	virtual void run();	

};



#endif