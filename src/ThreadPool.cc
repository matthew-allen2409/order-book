#include <shared_mutex>
#include <functional>
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i; i < numThreads; i++) {
        while (!stop) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return !taskQueue.empty() || stop; });

                if (stop && taskQueue.empty()) {
                    return;
                }

                task = std::move(taskQueue.front());
                taskQueue.pop();
            }

            task();
        }
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for (auto& worker:workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::enqueue_task(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(std::move(task));
    }
    condition.notify_one();
}
