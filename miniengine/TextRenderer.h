#pragma once
#include "Renderer.h"
#include "SFML/Graphics/Text.hpp"

namespace mini
{
	class TextRenderer : public mini::Renderer
	{
	private:
		sf::Text text;
	public:
		TextRenderer(GameObject& owner);
		virtual ~TextRenderer();
		virtual void setColor(const sf::Color& newColor) override;
		void setFont(const std::shared_ptr<sf::Font>& font);
		void setText(const std::string& str);
		void setCharacterSize(int size);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void getLocalBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const override;
	private:
		void adjustSize();
	};
}
