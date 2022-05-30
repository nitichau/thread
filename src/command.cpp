#include "../include/command.h"
#include<iostream> 
std::mutex printMtx;
void TestCommand::Execute()
{
	static int count = 0;
	std::cout<<"Executing sleep for 10 sec , task : "<<count<<"\n";
	std::this_thread::sleep_for(std::chrono::seconds(10));
	printMtx.lock();
	std::cout<<"Finished task :%d"<<++count<<"\n";
	printMtx.unlock();
}
