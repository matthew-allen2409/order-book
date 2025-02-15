#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <atomic>

using Task = std::function<void()>;

class ThreadPool {
public:
    ThreadPool(size_t numThreads);

    ~ThreadPool();

    void enqueue_task(Task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

#endif
