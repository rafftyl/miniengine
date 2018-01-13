#include "Miniengine.h"
#include "EngineSystems.h"
#include <SFML/Graphics.hpp>

namespace mini
{
	Miniengine::Miniengine()
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(200, 200), "SFML works!");
		systems.push_back(std::make_unique<AudioSystem>(msgBus));
		systems.push_back(std::make_unique<GameplaySystem>(msgBus));		
		systems.push_back(std::make_unique<InputSystem>(msgBus, *window));
		systems.push_back(std::make_unique<RenderingSystem>(msgBus, *window));
		systems.push_back(std::make_unique<GUISystem>(msgBus, *window));

		msgBus.onEngineShutdownRequest().addCallback([&] {shouldRun = false;});
	}

	Miniengine::~Miniengine()
	{
		window->close();
	}

	void Miniengine::Run()
	{
		while (shouldRun)
		{
			for (const auto& sys : systems)
			{
				sys->update();
			}
		}
	}
}