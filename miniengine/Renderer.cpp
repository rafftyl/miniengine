#include "Renderer.h"
#include "GameObject.h"

namespace mini
{
	Renderer::Renderer(GameObject& owner) : Component(owner)
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::update()
	{
	}

	void Renderer::setColor(const sf::Color& newColor)
	{
		color = newColor;
	}

	int Renderer::getLayer() const
	{
		return layer;
	}

	void Renderer::setLayer(int newLayer)
	{
		layer = newLayer;
	}

	void Renderer::getBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const
	{
		getLocalBounds(outMin, outMax);
		outMin = owner.getTransform() * outMin;
		outMax = owner.getTransform() * outMax;
	}
}