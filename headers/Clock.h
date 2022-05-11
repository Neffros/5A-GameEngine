#pragma once

#include <chrono>

struct Clock {
public: // seconds
    double const startTime;   // time of clock start
    double elapsedTime; // elapsed time since clock start
    double deltaTime;   // time since last frame
    double fixedDeltaTime;

    Clock() : startTime(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count()), elapsedTime(0), deltaTime(0), fixedDeltaTime(0){}

    void update(){
        auto end = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
        double currentTime = end - startTime;

        deltaTime = currentTime - elapsedTime;
        elapsedTime = currentTime;
    }
};