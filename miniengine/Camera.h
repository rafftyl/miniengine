#pragma once
#include "Component.h"
#include "RenderingQueue.h"
#include <set>
#include "SFML/System/Vector2.hpp"

namespace sf { class RenderWindow; }
namespace mini
{
	class Camera : public Component
	{
		friend class RenderingSystem;
		friend class GameplaySystem;
	private:
		std::set<std::shared_ptr<class Renderer>> renderers;	
		std::set<std::shared_ptr<class Renderer>> overlayRenderers;
		sf::Vector2f orthoSize;
	public:
		Camera(GameObject& owner);
		virtual ~Camera();				
		sf::Vector2f screenToWorldPoint(const sf::Vector2f& screenPoint) const;
		sf::Vector2f worldToScreenPoint(const sf::Vector2f& worldPoint) const;
		void setOrthoSize(const sf::Vector2f& size);
		sf::Vector2f getOrthoSize() const;
	private:
		void render(sf::RenderWindow& window) const;
		void registerRenderer(const std::shared_ptr<Renderer>& renderer);
		void unregisterRenderer(const std::shared_ptr<Renderer>& renderer);
		void renderSet(const std::set<std::shared_ptr<Renderer>>& rendererSet, sf::RenderWindow& window, bool cull) const;
	};
}
