#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>


class ThreadPool {
public:
    ThreadPool(int numThreads);

    ~ThreadPool();

    void enqueue_task(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

#endif
