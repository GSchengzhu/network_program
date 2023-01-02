#include "thread_pool.h"

ThreadPool* ThreadPool::getInstace()
{
    std::once_flag flag;
    std::call_once(flag,[&]{
        m_instace = new ThreadPool();
    });

    return m_instace;
}

ThreadPool::ThreadPool(int thread_nums)
{
    for(int i = 0; i < thread_nums; i++)
    {
        std::thread tmpThread(std::bind(work,this));
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
                m_condition.wait(locker);
            }
            func = m_queue.front();
            m_queue.pop();
        }

        if(func)
        {
            func();
        }
    }
    

}