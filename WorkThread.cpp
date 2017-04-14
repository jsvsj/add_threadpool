#include"WorkThread.h"
#include"Addthreadpool.h"
#include"PostThread.h"
#include<iostream>



WorkThread::WorkThread(int thread_id,Addthreadpool *pool)
	:thread_id_(thread_id),
	pool_(pool),
	mutex_(),
	cond_(mutex_)
{
	
}

void WorkThread::addTask(Task *task)
{

	MutexManager mmger(mutex_);
	task_queue_.push_back(task);
	cout<<"push_back"<<endl;
	cond_.notify();

}

Task* WorkThread::getTask()
{
	Task* task=NULL;
	MutexManager mmger(mutex_);
	while(task_queue_.empty()&& pool_->isRunning())
	{
		cond_.wait();
	}
	task=task_queue_.front();
	task_queue_.pop_front();
	return task;
}


void WorkThread::run()
{
	cout<<"WorkThread"<<endl;
	while(pool_->isRunning())
	{
		Task* task=this->getTask();
		if(task)
		{
			cout<<"["<<pthread_self()<<"]calc thread do task"<<endl;
			task->calc();
			vector<PostThread *> * pthreads=pool_->getPthreads();
			int id=task->getThreadId();
			(*pthreads)[id]->addTask(task);
		}
	}
	
}


WorkThread::~WorkThread()
{
	
}





