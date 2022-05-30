#ifndef COMMAND_H
#define COMMAND_H

#include<thread>
#include<vector>
#include<queue> 
#include<mutex>

class ICommand
{
public:
	virtual void Execute() = 0;
};

class TestCommand : public ICommand
{
public:
	virtual void Execute();
};

#endif 
