#include <iostream>

#include "include/ECS.h"

struct Transform
{
	float position;
};

int main()
{
	GameEngine::Engine engine;

	engine.registerComponent<Transform>();

	auto entity = engine.createEntity();

	engine.addComponent(entity, Transform{});

	engine.tick();

	std::cout << entity << std::endl;
}