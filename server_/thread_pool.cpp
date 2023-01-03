#include "thread_pool.h"

ThreadPool* ThreadPool::m_instace = nullptr;
ThreadPool* ThreadPool::getInstace()
{
    static std::once_flag flag;
    std::call_once(flag,[&]{
        m_instace = new ThreadPool();
        printf("inininininin\n");
    });

    return m_instace;
}

ThreadPool::ThreadPool(int thread_nums)
{
    m_runflag = true;
    for(int i = 0; i < thread_nums; i++)
    {
        std::thread tmpThread(std::bind(&ThreadPool::work,this));
        tmpThread.detach();
    }
}

void ThreadPool::work()
{
    while (m_runflag)
    {
        std::function<void()> func = nullptr;
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            if(m_queue.empty())
            {
                m_condition.wait(locker,[&]{
                    return !m_queue.empty();
                });
            }
            if(!m_queue.empty())
            {
                func = m_queue.front();
                m_queue.pop();
            }
            else
            {
                printf("current empty\n");
            }
            
        }

        if(func != nullptr)
        {
            func();
        }
    }
}