#include "Camera.h"
#include "MessageBus.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Renderer.h"
#include "Screen.h"

namespace mini
{
	Camera::Camera(GameObject& owner) : Component(owner)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::render(sf::RenderWindow& window) const
	{
		sf::View view(owner.getPosition(), orthoSize);
		window.setView(view);
		renderSet(renderers, window, true);
		window.setView(window.getDefaultView());
		renderSet(overlayRenderers, window, false);
	}

	void Camera::renderSet(const std::set<std::shared_ptr<Renderer>>& rendererSet, sf::RenderWindow& window, bool cull) const
	{
		RenderingQueue renderingQueue;
		for (auto& rend : rendererSet)
		{
			if (rend->getOwner().isActive())
			{
				//TODO: culling
				renderingQueue.push(rend);
			}
		}

		while (!renderingQueue.empty())
		{
			window.draw(*renderingQueue.top());
			renderingQueue.pop();
		}
	}

	void Camera::registerRenderer(const std::shared_ptr<Renderer>& renderer)
	{
		if (renderer->getOwner().isScreenSpace())
		{
			overlayRenderers.insert(renderer);
		}
		else
		{
			renderers.insert(renderer);
		}		
	}

	void Camera::unregisterRenderer(const std::shared_ptr<Renderer>& renderer)
	{
		if (renderer->getOwner().isScreenSpace())
		{
			overlayRenderers.erase(renderer);
		}
		else
		{
			renderers.erase(renderer);
		}				
	}

	sf::Vector2f Camera::screenToWorldPoint(const sf::Vector2f& screenPoint) const
	{
		sf::Vector2f uniformCoords(screenPoint.x / Screen::width, screenPoint.y / Screen::height);
		sf::Vector2f min = owner.getPosition() - orthoSize * 0.5f;
		return min + sf::Vector2f(uniformCoords.x * orthoSize.x, uniformCoords.y * orthoSize.y);
	}

	sf::Vector2f Camera::worldToScreenPoint(const sf::Vector2f& worldPoint) const
	{
		sf::Vector2f uniformCoords(worldPoint.x / orthoSize.x, worldPoint.y / orthoSize.y);
		sf::Vector2f min;
		return min + sf::Vector2f(uniformCoords.x * Screen::width, uniformCoords.y * Screen::height);
	}

	void Camera::setOrthoSize(const sf::Vector2f& size)
	{
		orthoSize = size;
	}

	sf::Vector2f Camera::getOrthoSize() const
	{
		return orthoSize;
	}
}