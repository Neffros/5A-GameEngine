#include <chrono>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

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

	auto entity = engine.createEntity("test");
	auto entity2 = engine.createEntity("another");
    auto entity3 = engine.createEntity("test");

	engine.addComponent(entity, Transform{});
    engine.addComponent(entity, Rigidbody{});
	engine.addComponent(entity2, Transform{});

    std::string tag = "test";
    std::vector<GameEngine::EntityId> ids = engine.getEntitiesByTag(tag);
    double startTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");
    sf::Font font;
    if(!font.loadFromFile("resources/arial.ttf")){
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setFillColor(sf::Color::White);
    while(window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

        if(currentTime - startTime < frameDuration)
            continue;

        engine.tick();
        startTime = currentTime;
        fpsText.setString("60");

        window.draw(fpsText);

        window.display();
    }

    engine.stop();
    return 0;
}
