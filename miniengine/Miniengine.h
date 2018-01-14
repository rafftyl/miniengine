#pragma once
#include "EngineSystem.h"
#include "MessageBus.h"
#include <vector>
#include <memory>

namespace sf { class RenderWindow; }
namespace mini
{
	struct EngineSettings
	{
		int windowWidth;
		int windowHeight;
		std::string windowName;
	};

	class Miniengine
	{
	private:
		MessageBus msgBus;
		std::vector<std::shared_ptr<EngineSystem>> systems;
		std::unique_ptr<sf::RenderWindow> window; //unique_ptr to avoid passing sfml header dependencies
		bool shouldRun = true;		
	public:
		Miniengine(const EngineSettings& settings, std::vector<class Scene>&& scenes);
		~Miniengine();
		void Run();
	};
}