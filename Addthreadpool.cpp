#include"Addthreadpool.h"
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include"PostThread.h"
#include"WorkThread.h"

Addthreadpool::Addthreadpool(unsigned int pthreads_num,unsigned int wthreads_num)
	:isrunning_(false),
	pthreads_num_(pthreads_num),
	wthreads_num_(wthreads_num),
	mutex_(),
	cond_(mutex_)
{
	//MutexManager
}

void Addthreadpool::start()
{
	
	srand(time(NULL));
	cout<<"start"<<endl;
	isrunning_=true;
	for(int i=0;i<wthreads_num_;++i)
	{
		WorkThread *thread=new WorkThread(i,this);
		wthreads_.push_back(thread);
		wthreads_[i]->start();
	}
	
	for(int i=0;i<pthreads_num_;++i)
	{
		PostThread *thread=new PostThread(i,this);
		pthreads_.push_back(thread);
		pthreads_[i]->start();
	}
	
	int index=0;
	while(isrunning_)
	{
		Task* task=this->getTask();
		cout<<"["<<pthread_self()<<"] main thread do transe"<<endl;
		
		wthreads_[index]->addTask(task);
		index=(index+1)%wthreads_num_;
	}
	
}

void Addthreadpool::stop()
{
	{
		MutexManager mmg(mutex_);
		  
		isrunning_ = false;
		  //唤醒所有的等待线程
		cond_.notifyAll();
	}
	for(int i=0;i<pthreads_num_;++i)
	{
		pthreads_[i]->join();
		delete pthreads_[i];
	}
	
	for(int i=0;i<wthreads_num_;++i)
	{
		wthreads_[i]->join();
		delete wthreads_[i];
	}
	cout<<"Addthreadpool::~Addthreadpool"<<endl;
	
}

void Addthreadpool::addTask(Task *task)
{
	if(wthreads_.empty())
	{
		cout<<"empty"<<endl;
		task->calc();
	}
    else
    {
		MutexManager mmger(mutex_);
		task_queue_.push_back(task);
		cout<<"push_back"<<endl;
		cond_.notify();
    }
	
}



Task* Addthreadpool::getTask()
{
	Task* task=NULL;
	MutexManager mmger(mutex_);
	while(task_queue_.empty()&&isrunning_)
	{
		cond_.wait();
	}
	task=task_queue_.front();
	task_queue_.pop_front();
	return task;
}







Addthreadpool::~Addthreadpool()
{
	if(isrunning_)
	{
		stop();
	}
	
}



















