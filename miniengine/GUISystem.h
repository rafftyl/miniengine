#pragma once
#include "EngineSystem.h"

namespace sf { class RenderWindow; }
namespace mini
{
	class GUISystem : public EngineSystem
	{
	private:
		sf::RenderWindow& window;
	public:
		GUISystem(MessageBus& msgBus, sf::RenderWindow& window);
		virtual ~GUISystem();
	};
}
