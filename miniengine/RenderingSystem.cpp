#include "RenderingSystem.h"
#include <SFML\Graphics.hpp>

namespace mini
{
	RenderingSystem::RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{
		debugCircle = new sf::CircleShape{ 100.f };
		msgBus.inputEvents.onMouseDrag.addCallback([&](sf::Mouse::Button button, const sf::Vector2i& mousePos, const sf::Vector2f& mouseDelta) {debugCircle->move(mouseDelta);});
	}

	RenderingSystem::~RenderingSystem()
	{
		delete debugCircle;
	}

	void RenderingSystem::update()
	{		
		EngineSystem::update();
		debugCircle->setFillColor(sf::Color::Green);
		window.clear();
		window.draw(*debugCircle);
		window.display();
	}
}
