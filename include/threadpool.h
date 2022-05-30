#ifndef THREADPOOL_H
#define THREADPOOL_H

#include"blockq.h"
#include"command.h"
#include<queue>
#include<vector>
#include<mutex>
#include<thread>

using namespace std;

class ThreadPool;

class Worker
{
public:
        Worker(ThreadPool& pool) :m_Pool(pool), m_bBoolStatus(false), m_bRunning(true)
        {
           m_Thread = new thread(&Worker::Threadwork, this);
        }

        void Join()
        {
           m_Thread->join();
        }

private:
        void Threadwork(); // not defined here .

        bool m_bBoolStatus;
        thread* m_Thread; // thread class from cpp .

        volatile bool m_bRunning;

        ThreadPool& m_Pool; //threadpool from our defined one .
};


class ThreadPool
{
  public:
        ThreadPool(int nSize = thread::hardware_concurrency()) :m_nSize(nSize), m_bRunning(true)
        {
           cout<<"Threadpool construct , num : "<<nSize<<"\n";
        }

        ~ThreadPool()
        {
           ShutDown();
        }

        void Enque(ICommand * cmd)
        {
                cout<<"Enqueue a task in a queue"<<"\n";
                mtxThreadJob.lock();
                m_Jobs.push(cmd);
                mtxThreadJob.unlock();
                m_Cv.notify_one();
        }

        void Start()
        {
                for (int i = 0; i < m_nSize; i++)
                {
                    Worker *pWorker = new Worker(*this);
                    m_Workers.push_back(pWorker);

                } // End of For
        }//Start end

        void ShutDown()
        {
		
              cout<<"Start a shutdown sequence"<<"\n";
              {
                unique_lock lock(mtxThreadStatus);
                m_bRunning = false;
              }
             m_Cv.notify_all();
             // Join all threads.
	     //
              for (Worker *worker : m_Workers)
              {
                worker->Join();
                delete worker;
               }

            m_Workers.clear();
        }

        volatile bool& Running()
        {
           return m_bRunning;
        }

        condition_variable& GetCondition()
        {
           return m_Cv;
        }

  private:
         BlockQ<ICommand *>& GetQueue()
         {
           return m_Jobs;
         }

         vector<Worker*> m_Workers;
         BlockQ<ICommand*> m_Jobs; // Define the jobs queue

         volatile bool m_bRunning;
         mutex mtxThreadStatus ; //Mutex on thread status
         mutex mtxThreadJob;   // Mutex on threaf job

         int m_nSize;
         condition_variable m_Cv;
         friend class Worker;
};
#endif 
