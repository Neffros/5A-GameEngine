#include "../headers/ThreadPool.h"

using namespace GameEngine;

void ThreadPool::Start() {
    const unsigned int nThreads = std::thread::hardware_concurrency();
    _threads.resize(nThreads);
    for (int i = 0; i < nThreads; ++i) {
        _threads.at(i) = std::thread(&ThreadPool::ThreadLoop, this);
    }
}

void ThreadPool::ThreadLoop() {
    while (true) {
        std::function <void()> job;
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _mutexCondition.wait(lock, [this] {
                return !_jobs.empty() || _shouldTerminate;
            });
            if (_shouldTerminate) {
                return;
            }
            job = _jobs.front();
            _jobs.pop();
        }
        job();
    }
}

void ThreadPool::QueueJob(const std::function<void()> &job) {
    std::unique_lock<std::mutex> lock(_queueMutex);
    _jobs.push(job);
}

void ThreadPool::Stop() {
    std::unique_lock<std::mutex> lock(_queueMutex);
    _shouldTerminate = true;

    _mutexCondition.notify_all();
    for(std::thread& activeThread : _threads){
        activeThread.join();
    }
    _threads.clear();
}
