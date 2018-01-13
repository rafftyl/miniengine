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
}