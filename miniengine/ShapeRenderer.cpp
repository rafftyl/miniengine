#include "ShapeRenderer.h"
#include "GameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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

	void ShapeRenderer::tempUglyHack() const
	{
		//temporary hack to force linker to include sfml shape definition (to avoid wrapping sfml shape classes)
		sf::CircleShape shape;
		shape.setFillColor(sf::Color::Blue);
		sf::RectangleShape shapee;
		shapee.setFillColor(sf::Color::Red);
	}
}