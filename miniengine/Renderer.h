#pragma once
#include "Component.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
namespace mini
{
	class Renderer : public Component, public sf::Drawable
	{
	private:
		int layer = 0;
	protected:
		sf::Color color = sf::Color::White;
	public:
		Renderer(GameObject& owner);
		virtual ~Renderer();
		virtual void setColor(const sf::Color& newColor);
		int getLayer() const;
		void setLayer(int newLayer);
		virtual void getBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const;
		virtual void getLocalBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const = 0;
	protected:
		virtual void update() override;			
	};
}


