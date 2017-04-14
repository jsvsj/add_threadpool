#include"PostThread.h"
#include"Addthreadpool.h"
#include<iostream>
#include<stdlib.h>
#include<unistd.h>

PostThread::PostThread(int thread_id,Addthreadpool *pool)
	:thread_id_(thread_id),
	pool_(pool),
	mutex_(),
	cond_(mutex_)
{
	
}

PostThread::~PostThread()
{
		
}


Task* PostThread::getTask()
{
	Task* task=NULL;
	MutexManager mmger(mutex_);
	while(task_queue_.empty() && pool_->isRunning())
	{
		cond_.wait();
	}
	task=task_queue_.front();
	task_queue_.pop_front();
	return task;
}

void PostThread::addTask(Task *task)
{

	MutexManager mmger(mutex_);
	task_queue_.push_back(task);
	cout<<"push_back"<<endl;
	cond_.notify();
}

void PostThread::run()
{
	int a,b;
	while(pool_->isRunning())
	{
		a=rand()%5000;
		b=rand()%5000;
		Task* task=new Task(a,b,thread_id_);
		cout<<"PostThread"<<endl;
		
		pool_->addTask(task);
		cout<<"["<<pthread_self()<<"]calc thread add task "<<a<<" + "<<b<<endl;
	
		Task* result_task=this->getTask();
		if(result_task)
		{
			result_task->show();
			cout<<"delete result_task;"<<endl;
			delete result_task;
		}
		sleep(1);
	}
	
}




