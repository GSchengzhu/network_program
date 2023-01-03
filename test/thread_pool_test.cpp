#include "../server_/thread_pool.h"
#include <stdio.h>
#include <unistd.h>

void test_1()
{
    printf("test_1\n");
    sleep(2);
}

void test_2()
{
    printf("test_2\n");
    sleep(2);
}

int g_num = 0;
void addwork()
{
    while (1)
    {
        if(g_num == 0)
        {
            g_num = 1;
            ThreadPool::getInstace()->addWork(test_1);
        }else
        {
            g_num = 0;
            ThreadPool::getInstace()->addWork(test_2);
        }
        sleep(1);
    }
    
    
}

int main()
{
    ThreadPool* thread_pool = ThreadPool::getInstace();
    std::thread thread_add(addwork);
    printf("111\n");
    while (true)
    {
        pause();
    }
}