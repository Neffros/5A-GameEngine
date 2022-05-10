#include <iostream>
#include <chrono>
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
    while(1){
        double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
        if(currentTime - startTime < frameDuration) {
            continue;
        }
        engine.tick();
        startTime = currentTime;
    }

	//std::cout << entity << " ; " << entity2 << std::endl;
}