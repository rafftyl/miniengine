#include "TextRenderer.h"
#include "GameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace mini
{
	TextRenderer::TextRenderer(GameObject& owner) : Renderer(owner)
	{
	}

	TextRenderer::~TextRenderer()
	{
	}

	void TextRenderer::setColor(const sf::Color& newColor)
	{
		text.setFillColor(newColor);
	}

	void TextRenderer::setFont(const std::shared_ptr<sf::Font>& font)
	{
		text.setFont(*font);		
	}

	void TextRenderer::setText(const std::string& str)
	{
		text.setString(str);
		adjustSize();
	}

	void TextRenderer::setCharacterSize(int size)
	{
		text.setCharacterSize(size);
		adjustSize();
	}

	void TextRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform = owner.getTransform() * states.transform;
		target.draw(text, states);
	}

	void TextRenderer::getLocalBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const
	{
		auto bounds = text.getLocalBounds();
		outMin.x = bounds.left;
		outMin.y = bounds.top - bounds.height;
		outMax.x = bounds.left + bounds.width;
		outMax.y = bounds.top;

		auto origin = text.getOrigin();
		origin.y *= -1;
		outMin -= origin;
		outMax -= origin;
	}

	void TextRenderer::adjustSize()
	{
		sf::Vector2f min, max;
		getLocalBounds(min, max);
		sf::Vector2f center = 0.5f * (max - min);
		text.setOrigin(center);
	}

}