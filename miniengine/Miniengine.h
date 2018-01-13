#pragma once
#include "EngineSystem.h"
#include "MessageBus.h"
#include <vector>
#include <memory>
namespace sf { class RenderWindow; }
namespace mini
{
	class Miniengine
	{
	private:
		MessageBus msgBus;
		std::vector<std::unique_ptr<EngineSystem>> systems;
		std::unique_ptr<sf::RenderWindow> window; //unique_ptr to avoid passing sfml header dependencies
		bool shouldRun = true;
	public:
		Miniengine();
		~Miniengine();
		void Run();
	protected:
	};
}