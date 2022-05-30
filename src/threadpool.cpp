
#include<iostream>
#include<thread>
#include<vector>
#include<queue> 
#include <mutex>
#include"../include/command.h"
#include"../include/threadpool.h"

int main()
{
    std::cout<< "thread pool start !\n"; 
    int val;
	ThreadPool pool;
	pool.Start();
	for (int i = 0; i < 10; i++)
	{
		ICommand * cmd = new TestCommand();
		pool.Enque(cmd);
	}

	for (int i = 0; i < 15; i++)
	{
		ICommand * cmd = new TestCommand();
		pool.Enque(cmd);
	}

	std::cin>>val;	 
	cout<<" val :"<<val<<"\n";
}  

