
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <pthread.h>
#include <vector>
#include <deque>
#include "Thread.h"


class ThreadPool
{
    public:
        typedef boost::function<void()> Task;
        ThreadPool(int n);
        ~ThreadPool();
        
        void run(Task task);
        void runInLoop(int idx);
        Task take();

    private:
        pthread_mutex_t mutex_;
        pthread_cond_t cond_;
        int threadnum_;
        bool isRunning_;
        std::deque<Task> tasks_;
        std::vector<Thread*> threads_;

};


#endif
