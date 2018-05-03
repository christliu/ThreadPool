#ifndef THREAD_H
#define THREAD_H

#include <boost/function.hpp>
#include <pthread.h>


class Thread
{
    public:
        typedef boost::function<void()> ThreadFunc;
        Thread(ThreadFunc func);
        ~Thread();
        void start();
        int join();

        pthread_t GetThreadId()
        {
            return threadid_;
        }

    private:
        ThreadFunc func_;
        pthread_t threadid_;
        bool joined_;

};

#endif
