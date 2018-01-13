#include "ShapeRenderer.h"
#include "GameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace mini
{
	ShapeRenderer::ShapeRenderer(GameObject& owner) : Renderer(owner)
	{
	}

	ShapeRenderer::~ShapeRenderer()
	{
	}

	void ShapeRenderer::setShape(const std::shared_ptr<sf::Shape>& sharedShape)
	{
		shape = sharedShape;
	}

	void ShapeRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		shape->setFillColor(color);
		states.transform = owner.getTransform() * states.transform;
		target.draw(*shape, states);
	}
}