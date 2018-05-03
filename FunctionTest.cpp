#include <boost/function.hpp>
#include <stdio.h>


void show()
{
    printf("in show\n");
}


class Fun
{
    public:
        typedef boost::function<void()> task;
        Fun(const task& t):task_(t){}

        void run()
        {
            task_();
        }

    private:
        task task_;
};


int main()
{
    Fun wf(show);
    wf.run();
    return 0;
}
