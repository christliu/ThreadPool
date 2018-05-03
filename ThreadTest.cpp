#include "Thread.h"
#include <stdio.h>
#include <boost/bind.hpp>

void print()
{
    printf("in thread\n");
    return;
}

void show(int a)
{
    printf("in show arg %d\n", a);
    return;
}

int main()
{
    Thread t(boost::bind(show, 1));
    t.start();
    t.join();
    return 0;
}

