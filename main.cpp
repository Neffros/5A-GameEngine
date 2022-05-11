#include <iostream>

#include "include/ECS.h"

struct Transform
{
	float position;
};

struct Rigidbody
{
	float velocity;
};

class MoveSystem : public GameEngine::System<Transform, Rigidbody>
{
	virtual void behaviour(const GameEngine::EntityId& id, Transform& transform, Rigidbody& rigidbody) const override
	{
		transform.position += 2;
		std::cout << transform.position << std::endl;
	}
};

int main()
{
	GameEngine::Engine engine;

	engine.registerComponent<Transform>();
	engine.registerComponent<Rigidbody>();
	engine.registerSystem<MoveSystem>();

	auto entity = engine.createEntity();

	engine.addComponent(entity, Transform{});
	engine.addComponent(entity, Rigidbody{});

	int i = 0;

	while (i < 50000)
		engine.tick();
}