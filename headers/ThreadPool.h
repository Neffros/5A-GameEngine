#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>

namespace GameEngine {
    class ThreadPool {
    public:
        void Start();

        void QueueJob(const std::function<void()> &job);

        void Stop();

    private:
        void ThreadLoop();

        bool _shouldTerminate = false;
        std::mutex _queueMutex;
        std::condition_variable _mutexCondition;
        std::vector<std::thread> _threads;
        std::queue<std::function<void()>> _jobs;
    };
}