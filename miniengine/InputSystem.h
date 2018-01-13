#pragma once
#include "EngineSystem.h"
#include <SFML/System/Vector2.hpp>
#include <map>
namespace sf { class RenderWindow; }

namespace mini
{
	class InputSystem : public EngineSystem
	{
	private:	
		const float timeToBroadcastHoldEvent = 0.1f;
		const float timeToBroadcastDragEvent = 0.1f;

		sf::RenderWindow& window;
		std::map<sf::Keyboard::Key, float> pressedKeys;
		std::map<sf::Mouse::Button, float> pressedMouseButtons;
		sf::Vector2f mousePosition{ 0, 0 };
		sf::Vector2f mouseDelta{ 0, 0 };

		bool isMouseDragging = false;
	public:
		InputSystem(MessageBus& msgBus, sf::RenderWindow& window);
		virtual ~InputSystem();

		virtual void update() override;
	private:
		void registerKeyPress(sf::Keyboard::Key key, const ModifierKeys& mods);
		void registerMouseButtonPress(sf::Mouse::Button button);
		void handleMouseMove(const sf::Vector2i& mousePos);
		void handleMouseScroll(sf::Mouse::Wheel wheel, float delta);
		void advanceHoldTimers();
		void broadcastHoldEvents() const;
	};
}
