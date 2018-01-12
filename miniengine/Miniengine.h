#pragma once
#include "Defines.h"
#include "EngineSystem.h"
#include "MessageBus.h"
#include <vector>
#include <memory>
namespace sf { class RenderWindow; }
namespace mini
{
	class MiniengineImpl
	{
	private:
		MessageBus msgBus;
		std::vector<std::unique_ptr<EngineSystem>> systems;
		std::unique_ptr<sf::RenderWindow> window; //unique_ptr to avoid passing sfml header dependencies
		bool shouldRun = true;
	public:
		MiniengineImpl();
		~MiniengineImpl();
		void Run();
	protected:
	};

	//pimpl technique to avoid exporting stl containers in dll
	class MINI_API Miniengine
	{
	private:
		MiniengineImpl* impl;
	public:
		Miniengine();
		~Miniengine();
		void Run();
	};
	
}