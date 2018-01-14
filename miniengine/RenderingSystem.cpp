#include "RenderingSystem.h"
#include <SFML\Graphics.hpp>
#include "ShapeRenderer.h"

namespace mini
{
	RenderingSystem::RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{		
		msgBus.engineEvents.onCreateRenderingQueue.addCallback(
		[&](const RenderingQueue& queue)
		{			
			renderingQueue = queue;
		});
	}

	RenderingSystem::~RenderingSystem()
	{		
	}

	void RenderingSystem::update()
	{		
		EngineSystem::update();
		window.clear();
		while (!renderingQueue.empty())
		{
			window.draw(*renderingQueue.top());
			renderingQueue.pop();
		}
		window.display();
	}
}
