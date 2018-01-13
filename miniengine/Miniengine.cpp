#include "Miniengine.h"
#include "EngineSystems.h"
#include <SFML/Graphics.hpp>

namespace mini
{
	Miniengine::Miniengine(const EngineSettings& settings)
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(settings.windowWidth, settings.windowHeight), settings.windowName);
		systems.push_back(std::make_unique<AudioSystem>(msgBus));
		systems.push_back(std::make_unique<GameplaySystem>(msgBus));		
		systems.push_back(std::make_unique<InputSystem>(msgBus, *window));
		systems.push_back(std::make_unique<RenderingSystem>(msgBus, *window));
		systems.push_back(std::make_unique<GUISystem>(msgBus, *window));
		systems.push_back(std::make_unique<DebugConsole>(msgBus));

		msgBus.engineEvents.onEngineShutdownRequest.addCallback([&] {shouldRun = false;});
		msgBus.engineEvents.onEngineStart.broadcast();
	}

	Miniengine::~Miniengine()
	{
		window->close();
		msgBus.engineEvents.onEngineShutdown.broadcast();
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