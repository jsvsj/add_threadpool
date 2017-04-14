#ifndef _ADD_THREAD_POOL_H_
#define _ADD_THREAD_POOL_H_
#include<deque>
#include<iostream>
#include<vector>
#include"Thread.h"
#include"Mutex.h"
#include"Condition.h"


using namespace std;


class Addthreadpool;
class PostThread;
class WorkThread;

class Task:public nocopyable
{
	
public:
	Task(int a,int b,int thread_id)
		:a_(a),b_(b),thread_id_(thread_id),result_(-1)
	{
		
	}
	~Task()
	{
		cout<<"~Task()"<<endl;
	}
	void calc()
	{
		result_=a_+b_;
	}
	void show()
	{
		cout<<a_<<" + "<<b_<<" = "<<result_<<endl;
	}
	int getThreadId() const { return thread_id_; } 

private:
	int thread_id_;
	int a_;
	int b_;
	int result_;
	
};





class Addthreadpool
{

private:
	bool isrunning_;
	deque<Task *> task_queue_;
	unsigned int pthreads_num_;
	unsigned int wthreads_num_;
	vector<PostThread *> pthreads_;
	vector<WorkThread *> wthreads_;
	
	Mutex mutex_;
	Condition cond_;
		
public:
	vector<PostThread *> * getPthreads(){ return &pthreads_; }
	bool isRunning() const { return isrunning_; }
	void start();
	void stop();
	
	void addTask(Task * task);
	Task* getTask();
	
	Addthreadpool(unsigned int pthreads_num,unsigned int wthreads_num);
	~Addthreadpool();
};


#endif


