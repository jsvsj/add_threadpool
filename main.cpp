#include<stdio.h>
#include<stdlib.h>

#include"Condition.h"
#include"Addthreadpool.h"
#include<unistd.h>
#include<iostream>

using namespace std;

int main()
{
				  //post   work
	Addthreadpool pool(4,3);
	pool.start();
	return 0;
}
