#include "Renderer.h"

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
}