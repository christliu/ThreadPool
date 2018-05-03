#include "ThreadPool.h"
#include <stdlib.h>
#include <stdio.h>

void print()
{
    printf("in print\n");
}

int main()
{
    {
        ThreadPool p(3);
        p.run(print);

    }
    printf(" thread pool is destoryed\n");

    ThreadPool::Task task;
    if(task)
    {
        printf("task is true\n");
    }
    else
        printf("task is false\n");
    return 0;
}
