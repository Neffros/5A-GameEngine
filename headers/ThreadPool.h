#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

namespace GameEngine {
    struct Job {
    public:
        int id;
        std::function<void()> func;

        Job() : id(-1), func(nullptr) {}

        Job(int idP, std::function<void()> funcP) : id(idP), func(std::move(funcP)) {}
    };

    class ThreadPool {
    public:
        int QueueJob(const std::function<void()> &job);

        void Start();

        void Stop();

        void WaitForJob(int jobId);

    private:
        void ThreadLoop();

        std::map<int, bool> _idToStatus;
        std::queue<Job> _jobs;
        int _lastJobId;
        std::condition_variable _mutexCondition;
        std::mutex _queueMutex;
        bool _shouldTerminate = false;
        std::vector<std::thread> _threads;
    };
}