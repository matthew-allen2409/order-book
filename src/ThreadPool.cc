#include <mutex>
#include <functional>
#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) : stop(false) {
        for (int i = 0; i< numThreads; i++) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !taskQueue.empty(); });
                        if (stop && taskQueue.empty()) { return; }
                        task = taskQueue.front();
                        taskQueue.pop();
                    }

                    task();
                }
            });
        }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (auto& worker:workers) {
        worker.join();
    }
}

void ThreadPool::enqueue_task(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!stop) {
            taskQueue.push(std::move(task));
        }
    }
    condition.notify_one();
}
