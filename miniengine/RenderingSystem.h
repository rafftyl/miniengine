#pragma once
#include "EngineSystem.h"
#include "GameObject.h"
#include "RenderingQueue.h"
#include <memory>

namespace sf { class RenderWindow; class CircleShape; }
namespace mini
{
	class RenderingSystem : public EngineSystem
	{
	private:
		sf::RenderWindow& window;
		RenderingQueue renderingQueue;
	public:
		RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window);
		virtual ~RenderingSystem();

		virtual void update() override;
	};
}
