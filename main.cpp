#include <chrono>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "include/ECS.h"
#include "headers/Transform.h"

sf::RenderWindow* window;

struct Rigidbody
{
	float velocity;
};

class MoveSystem : public GameEngine::System<Transform, Rigidbody>
{
	void behaviour(const GameEngine::EntityId& id, Transform& transform, Rigidbody& rigidbody) const override
	{
		transform.position[0] += 0.5;
        std::cout << "Entity id : " << id << " ; Transform component : " << transform.toString() << std::endl;
	}
};

class RendererSystem : public GameEngine::System<Transform>{
    void run(GameEngine::Engine* engine, const std::set<GameEngine::EntityId>& entities) const override{
        auto& comps = engine->getComponents<Transform>();
        for (const auto& id : entities) {
            this->behaviour(id, comps[id]);
        }
    }
    void behaviour(const GameEngine::EntityId& id, Transform& transform) const override
	{
        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(transform.position[0], transform.position[1]);
        window->draw(shape);
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
    engine.registerSystem<RendererSystem>();

	auto entity = engine.createEntity("test");
	auto entity2 = engine.createEntity("another");
    auto entity3 = engine.createEntity("test");

	engine.addComponent(entity, Transform{});
    engine.addComponent(entity, Rigidbody{});
	engine.addComponent(entity2, Transform{});

    std::string tag = "test";
    std::vector<GameEngine::EntityId> ids = engine.getEntitiesByTag(tag);
    double startTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game Engine");
    sf::Font font;
    if(!font.loadFromFile("resources/arial.ttf")){
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setFillColor(sf::Color::White);
    int secondFrameCount = 0;
    sf::Clock fpsClock;
    while(window->isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window->pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear(sf::Color::Black);

        double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

        if(currentTime - startTime < frameDuration)
            continue;

        engine.tick();
        startTime = currentTime;
        sf::Time elapsed = fpsClock.getElapsedTime();
        ++secondFrameCount;
        if(elapsed.asSeconds() > 1){
            fpsText.setString("FPS: " + std::to_string(secondFrameCount));
            secondFrameCount = 0;
            fpsClock.restart();
        }

        window->draw(fpsText);

        window->display();
    }

    engine.stop();
    return 0;
}
