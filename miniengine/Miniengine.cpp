#include "Miniengine.h"
#include "EngineSystems.h"
#include <SFML/Graphics.hpp>

namespace mini
{
	MiniengineImpl::MiniengineImpl()
	{
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(200, 200), "SFML works!");
		systems.push_back(std::make_unique<AudioSystem>(msgBus));
		systems.push_back(std::make_unique<GameplaySystem>(msgBus));		
		systems.push_back(std::make_unique<InputSystem>(msgBus, *window));
		systems.push_back(std::make_unique<RenderingSystem>(msgBus, *window));
		systems.push_back(std::make_unique<GUISystem>(msgBus, *window));

		msgBus.onEngineShutdownRequest().addCallback([&](int arg, int arss) {shouldRun = false;});
	}

	MiniengineImpl::~MiniengineImpl()
	{
		window->close();
	}

	void MiniengineImpl::Run()
	{
		while (shouldRun)
		{
			for (const auto& sys : systems)
			{
				sys->update();
			}
		}
	}

	Miniengine::Miniengine()
	{
		impl = new MiniengineImpl();
	}

	Miniengine::~Miniengine()
	{
		delete impl;
	}

	void Miniengine::Run()
	{
		impl->Run();
	}
}