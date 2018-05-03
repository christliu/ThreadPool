#include "Thread.h"
#include <unistd.h>
#include <stdio.h>

struct ThreadArgs
{
    Thread::ThreadFunc f;
};

void* runInThread(void* args)
{
    ThreadArgs *a = static_cast<ThreadArgs*>(args);
    a->f();
    delete a;
    return NULL;
}


Thread::Thread(ThreadFunc func):func_(func), joined_(false), threadid_(0)
{
}

Thread::~Thread()
{
    if( !joined_)
    {
        pthread_detach(threadid_);
    }
}

void Thread::start()
{
    ThreadArgs *args = new ThreadArgs();
    args->f = func_;
    if(pthread_create(&threadid_, NULL, runInThread, (void*)args) !=0)
    {
        delete args;
        return;
    }
}


int Thread::join()
{
    joined_ = true;
    return pthread_join(threadid_, NULL);
}
