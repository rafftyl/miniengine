#include "RenderingSystem.h"
#include <SFML\Graphics.hpp>
#include "ShapeRenderer.h"

namespace mini
{
	RenderingSystem::RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{
		auto shape = std::make_shared<sf::CircleShape>(80.f);
		shape->setOrigin({ 80,80 });
		auto& shapeRen = debugCircle.addComponent<ShapeRenderer>();
		shapeRen.setColor(sf::Color::Green);
		shapeRen.setShape(shape);
		msgBus.inputEvents.onMouseDrag.addCallback(
		[&](sf::Mouse::Button button, const sf::Vector2f& mousePos, const sf::Vector2f& mouseDelta) 
		{			
			debugCircle.setPosition(mousePos);
		});
	}

	RenderingSystem::~RenderingSystem()
	{		
	}

	void RenderingSystem::update()
	{		
		EngineSystem::update();
		window.clear();
		window.draw(*debugCircle.getComponent<Renderer>());
		window.display();
	}
}
