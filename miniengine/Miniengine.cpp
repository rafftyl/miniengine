#include "Miniengine.h"
#include "EngineSystems.h"
#include "Timer.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>

namespace mini
{
	Miniengine::Miniengine(const EngineSettings& settings, std::vector<Scene>&& scenes)
	{
		Screen::width = settings.windowWidth;
		Screen::height = settings.windowHeight;
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(settings.windowWidth, settings.windowHeight), settings.windowName);
		systems.push_back(std::make_shared<InputSystem>(msgBus, *window));
		systems.push_back(std::make_shared<GameplaySystem>(msgBus, std::move(scenes)));
		systems.push_back(std::make_shared<AudioSystem>(msgBus));	
		systems.push_back(std::make_shared<RenderingSystem>(msgBus, *window));
		systems.push_back(std::make_shared<GUISystem>(msgBus, *window));
		systems.push_back(std::make_shared<DebugConsole>(msgBus));

		msgBus.engineEvents.onEngineShutdownRequest.addCallback([&] {shouldRun = false;});

		for (const auto& sys : systems)
		{
			sys->init();
		}

		msgBus.engineEvents.onEngineStart.broadcast();
		Time::updateTimer(); //to init timestamps		
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
			Time::updateTimer();					
			for (const auto& sys : systems)
			{
				sys->update();
			}
		}
	}
}