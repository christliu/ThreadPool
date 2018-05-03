#include <boost/bind.hpp>
#include <pthread.h>
#include <stdio.h>
#include "Thread.h"


class Pool
{
    public:
        Pool():num(0), lastOutput(-1), t1(boost::bind(&Pool::inc, this)), t2(boost::bind(&Pool::print, this)) 
        {
            pthread_mutex_init(&mutex_, NULL);
            pthread_cond_init(&cond_, NULL);
/*
            t1(boost::bind(&Pool::inc, this));
            t2(boost::bind(&Pool::print, this));
            */
            t1.start();
            t2.start();
        }
 
        ~Pool()
        {
            pthread_cond_destroy(&cond_);
            pthread_mutex_destroy(&mutex_);
        };

        void inc()
        {
            while(1)
            {
                sleep(1);
                pthread_mutex_lock(&mutex_);
                num ++;

                if(canNotify())
                {
                    pthread_cond_signal(&cond_);
                }
                pthread_mutex_unlock(&mutex_);
            }
        }

        void print()
        {
            while(1)
            {
                pthread_mutex_lock(&mutex_);
                while(!canNotify())
                {
                    pthread_cond_wait(&cond_, &mutex_);
                }

                printf("cur num %d\n", num);
                lastOutput = num;
                pthread_mutex_unlock(&mutex_);
            }
        }

        bool canNotify()
        {
            return num % 3 == 0 and num != lastOutput;
        }

        void join()
        {
            t1.join();
            t2.join();
        }

    private:
        pthread_cond_t cond_;
        pthread_mutex_t mutex_;
        Thread t1, t2;

        int num;
        int lastOutput;
};

int main()
{
    Pool p;
    p.join();
    return 0;
}
