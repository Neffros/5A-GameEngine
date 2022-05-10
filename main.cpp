#include <chrono>
#include <iostream>
#include "windows.h"
#include "include/ECS.h"

struct Transform
{
	float position;
};

int main()
{
    double frameRate = 60.0;
    double frameDuration = 1.0 / frameRate;
	GameEngine::Engine engine(frameRate);

	engine.registerComponent<Transform>();

	auto entity = engine.createEntity();
	auto entity2 = engine.createEntity();

	engine.addComponent(entity, Transform{});
	engine.addComponent(entity2, Transform{});

    double startTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

    bool loop = true;
    while(loop){
        if(GetKeyState('A') & 0x8000) {
            loop = false;
        }
        double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
        if(currentTime - startTime < frameDuration) {
            continue;
        }
        engine.tick();
        startTime = currentTime;
    }

    engine.stop();
    return 0;
}
