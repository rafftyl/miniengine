#include "RenderingSystem.h"
#include <SFML\Graphics.hpp>

RenderingSystem::RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window) :
	EngineSystem(msgBus), window(window)
{
}

RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::update()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.clear();
	window.draw(shape);
	window.display();	
}
