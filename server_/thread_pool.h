#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H

#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

class ThreadPool
{
public:
    static ThreadPool* getInstace();

    template<class F>
    void addWork(F&& task)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.emplace(std::forward<F>(task));
        m_condition.notify_one();
    }
    void work();

private:
    ThreadPool(int thread_nums = 10);


private:
    std::queue<std::function<void()>> m_queue;
    std::queue<std::thread> m_threads;
    static ThreadPool* m_instace;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_runflag;
};


#endif