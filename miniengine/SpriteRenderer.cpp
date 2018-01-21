#include "SpriteRenderer.h"
#include "GameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace mini
{
	SpriteRenderer::SpriteRenderer(GameObject& owner) : Renderer(owner)
	{
	}


	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::setSprite(const std::shared_ptr<sf::Sprite>& sharedSprite)
	{
		this->sprite = sprite;
	}

	void SpriteRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite->setColor(color);
		states.transform = owner.getTransform() * states.transform;
		target.draw(*sprite, states);
	}

	void SpriteRenderer::getLocalBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const
	{
		auto bounds = sprite->getLocalBounds();
		outMin.x = bounds.left;
		outMin.y = bounds.top - bounds.height;
		outMax.x = bounds.left + bounds.width;
		outMax.y = bounds.top;
		auto origin = sprite->getOrigin();
		origin.y *= -1;
		outMin -= origin;
		outMax -= origin;
	}
}