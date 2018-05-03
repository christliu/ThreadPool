#include <boost/bind.hpp>
#include <stdio.h>
#include "ThreadPool.h"

ThreadPool::ThreadPool(int n):threadnum_(n), isRunning_(true)
{
    pthread_cond_init(&cond_, NULL);
    pthread_mutex_init(&mutex_, NULL);

    for(int i = 0; i < n; i ++)
    {
        Thread* t = new Thread(boost::bind(&ThreadPool::runInLoop, this, i)) ;
        threads_.push_back(t);
        t->start();
    }
}

void ThreadPool::runInLoop(int idx)
{
    while(isRunning_)
    {
        ThreadPool::Task t(take());
        //TODO: judge if t
        if(t)
            t();
        printf("thread %d exit\n", idx);
    }
}


ThreadPool::Task ThreadPool::take()
{
    pthread_mutex_lock(&mutex_);
    while(tasks_.empty() && isRunning_)
    {
        printf("task wait here\n");
        pthread_cond_wait(&cond_, &mutex_);
    }
    Task task;
    if(!tasks_.empty())
    {
        task = tasks_.front();
        tasks_.pop_front();
    }
    pthread_mutex_unlock(&mutex_);
    return task;
}


void ThreadPool::run(Task task)
{
    pthread_mutex_lock(&mutex_);
    tasks_.push_back(task);
    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&mutex_);
}


ThreadPool::~ThreadPool()
{
    printf("in destructor\n");
    pthread_mutex_lock(&mutex_);
    isRunning_ = false;
    pthread_cond_broadcast(&cond_);
    pthread_mutex_unlock(&mutex_);
    for(std::vector<Thread*>::iterator it = threads_.begin(); it != threads_.end();++it)
    {
        (*it)->join();
        delete *it;
    }
    pthread_cond_destroy(&cond_);
    pthread_mutex_destroy(&mutex_);

}
