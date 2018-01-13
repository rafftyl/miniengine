#pragma once
#include "Component.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
namespace mini
{
	class Renderer : public Component, public sf::Drawable
	{
	protected:
		sf::Color color = sf::Color::White;
	public:
		Renderer(GameObject& owner);
		virtual ~Renderer();

		virtual void update(float deltaTime) override;	
		void setColor(const sf::Color& newColor);
	};
}


