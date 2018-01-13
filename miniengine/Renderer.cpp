#include "Renderer.h"

namespace mini
{
	Renderer::Renderer(GameObject& owner) : Component(owner)
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::update(float deltaTime)
	{
	}

	void Renderer::setColor(const sf::Color& newColor)
	{
		color = newColor;
	}
}