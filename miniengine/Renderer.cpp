#include "Renderer.h"
#include "GameObject.h"
#include "GameplaySystem.h"

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

	void Renderer::start()
	{
		if (getGameplaySystem().getCurrentCam() != nullptr)
		{
			getGameplaySystem().getCurrentCam()->registerRenderer(shared_from_this());
		}
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

	sf::Vector2f Renderer::getSize() const
	{
		sf::Vector2f min, max;
		getBounds(min, max);
		return max - min;
	}

	void Renderer::getBounds(sf::Vector2f& outMin, sf::Vector2f& outMax) const
	{
		getLocalBounds(outMin, outMax);
		outMin = owner.getTransform() * outMin;
		outMax = owner.getTransform() * outMax;
	}
}