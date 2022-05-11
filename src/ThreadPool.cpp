#include <iostream>
#include "../headers/ThreadPool.h"

using namespace GameEngine;

int ThreadPool::queueJob(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _idToStatus[_lastJobId] = false;
        _jobs.push(Job(_lastJobId, job));
    }
    _mutexCondition.notify_one();
    return _lastJobId++;
}

void ThreadPool::start()
{
    _lastJobId = 0;
    const unsigned int nThreads = std::thread::hardware_concurrency();
    _threads.resize(nThreads);
    for (int i = 0; i < nThreads; ++i) {
        _threads.at(i) = std::thread(&ThreadPool::threadLoop, this);
    }
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _shouldTerminate = true;
    }
    _mutexCondition.notify_all();
    for(std::thread& activeThread : _threads){
        activeThread.join();
    }
    _threads.clear();
}

void ThreadPool::threadLoop() {
    while (true)
    {
        Job job;
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
        job.func();
        _idToStatus[job.id] = true;
    }
}

void ThreadPool::waitForJob(int jobId)
{
    while(!_idToStatus[jobId]);
}
