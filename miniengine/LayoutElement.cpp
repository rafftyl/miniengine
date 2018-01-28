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
		refresh();
	}

	void LayoutElement::setPosition(const sf::Vector2f& pos)
	{
		elementPosition = pos;
	}

	void LayoutElement::setSize(const sf::Vector2f& size)
	{
		elementSize = size;
	}

	void LayoutElement::setPivotPosition(const sf::Vector2f& position)
	{
		uniformPivotPosition = position;
	}

	void LayoutElement::applySettings(const LayoutElementSettings& layoutSettings)
	{
		settings = layoutSettings;
	}

	void LayoutElement::refresh()
	{
		owner.setScreenSpace(true);
		renderer = owner.getComponent<Renderer>();
		sf::Vector2f min, max;
		renderer->getBounds(min, max);
		sf::Vector2f size = max - min;
		sf::Vector2f scale =
			sf::Vector2f(
				settings.absoluteSizeX ? elementSize.x / size.x : elementSize.x * Screen::width / size.x,
				settings.absoluteSizeY ? elementSize.y / size.y : elementSize.y * Screen::height / size.y);
		owner.setScale(scale);

		renderer->getBounds(min, max);
		size = max - min;
		uniformPivotPosition -= sf::Vector2f(0.5f, 0.5f);
		sf::Vector2f offset(uniformPivotPosition.x * size.x, uniformPivotPosition.y * size.y);
		sf::Vector2f pos =
			sf::Vector2f(settings.absolutePositionX ? elementPosition.x : elementPosition.x * Screen::width,
				settings.absolutePositionY ? elementPosition.y : elementPosition.y * Screen::height);
		pos -= offset;
		owner.setPosition(pos);
	}
}