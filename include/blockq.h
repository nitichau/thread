#ifndef BLOCKQ_H 
#define BLOCKQ_H
//Above is include guard 

#include <iostream>
#include<queue>
#include <mutex>
#include <condition_variable>

using namespace std ;

template <class T>
class BlockQ
{
public:
    BlockQ() { ; }
 
    void push(const T & data)
    {
        unique_lock<mutex> lock(mtx_lock);
        q_data.push(data);
        q_cv.notify_one();
    }
 
    void pop()
    {
        unique_lock<mutex> lock(mtx_lock);
        if(!q_data.empty())
            q_data.pop();
    }
 
    T& front()
    {
        unique_lock<mutex> lock(mtx_lock);
        q_cv.wait(lock, [&] { return  !q_data.empty(); });
        T& data = q_data.front();
        return data;
    }
 
    T& back()
    {
        unique_lock<mutex> lock(mtx_lock);
        q_cv.wait(lock, [&] { return  !q_data.empty(); });
        T& data = q_data.back();
        return data;
    }
 
 
    bool empty()
    {
        return q_data.empty();
    }
 
    size_t size()
    {
        return q_data.size();
    }
 
private:
    queue <T> q_data;
    condition_variable q_cv;
    mutex mtx_lock;
};


#endif 
