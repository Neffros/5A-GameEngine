#include <chrono>
#include <iostream>
#include "windows.h"

#include "include/ECS.h"
#include "headers/Transform.h"

struct Rigidbody
{
	float velocity;
};

class MoveSystem : public GameEngine::System<Transform, Rigidbody>
{
	void behaviour(const GameEngine::EntityId& id, Transform& transform, Rigidbody& rigidbody) const override
	{
		transform.position[0] += 2;
        std::cout << "Entity id : " << id << " ; Transform component : " << transform.toString() << std::endl;
	}
};

int main()
{
    double frameRate = 60.0;
    double frameDuration = 1.0 / frameRate;

	GameEngine::Engine engine(frameRate);

	engine.registerComponent<Transform>();
	engine.registerComponent<Rigidbody>();
	engine.registerSystem<MoveSystem>();

	auto entity = engine.createEntity();
	auto entity2 = engine.createEntity();

	engine.addComponent(entity, Transform{});
    engine.addComponent(entity, Rigidbody{});
	engine.addComponent(entity2, Transform{});

    double startTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

    bool loop = true;

    while(loop)
    {
        if(GetKeyState('A') & 0x8000)
            loop = false;

        double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

        if(currentTime - startTime < frameDuration)
            continue;

        engine.tick();
        startTime = currentTime;
    }

    engine.stop();
    return 0;
}
