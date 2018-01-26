#include "LayoutElement.h"
#include "GameObject.h"
#include "Screen.h"

namespace mini
{
	LayoutElement::LayoutElement(GameObject& owner) : Component(owner)
	{
	}

	LayoutElement::~LayoutElement()
	{
	}

	void LayoutElement::start()
	{
		Component::start();		
		renderer = owner.getComponent<Renderer>();
		sf::Vector2f min, max;
		renderer->getBounds(min, max);
		sf::Vector2f size = max - min;
		sf::Vector2f scale = absoluteSize ? 
			sf::Vector2f(elementSize.x / size.x, elementSize.y / size.y) :
			sf::Vector2f(elementSize.x * Screen::width / size.x, elementSize.y * Screen::height / size.y);
		owner.setScale(scale);
		renderer->getBounds(min, max);
		size = max - min;
		uniformPivotPosition -= sf::Vector2f(0.5f, 0.5f);
		sf::Vector2f offset(uniformPivotPosition.x * size.x, uniformPivotPosition.y * size.y);
		owner.setPosition(sf::Vector2f(uniformPosition.x * Screen::width, uniformPosition.y * Screen::height) - offset);
	}

	void LayoutElement::setUniformPosition(const sf::Vector2f& pos)
	{
		uniformPosition = pos;
	}

	void LayoutElement::setUniformSize(const sf::Vector2f& size)
	{
		elementSize = size;
		absoluteSize = false;
	}

	void LayoutElement::setAbsoluteSize(const sf::Vector2f& size)
	{
		elementSize = size;
		absoluteSize = true;
	}

	void LayoutElement::setPivotPosition(const sf::Vector2f& position)
	{
		uniformPivotPosition = position;
	}
}