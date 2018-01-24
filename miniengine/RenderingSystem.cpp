#include "RenderingSystem.h"
#include <SFML\Graphics.hpp>
#include "ShapeRenderer.h"
#include "Camera.h"

namespace mini
{
	RenderingSystem::RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{		
		msgBus.engineEvents.onCameraSet.addCallback(
		[&](const std::shared_ptr<Camera>& cam)
		{			
			currentCam = cam;
		});
	}

	RenderingSystem::~RenderingSystem()
	{		
	}

	void RenderingSystem::update()
	{		
		EngineSystem::update();
		window.clear();
		if (currentCam != nullptr)
		{
			currentCam->render(window);
		}
		window.display();
	}
}
