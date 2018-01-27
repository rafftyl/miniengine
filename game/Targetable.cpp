#include "Targetable.h"
#include "GameObject.h"

Targetable::Targetable(mini::GameObject& owner) : mini::Component(owner)
{
}

Targetable::~Targetable()
{
}

void Targetable::start()
{
	renderer = owner.getComponent<mini::Renderer>();
	renderer->setColor(normalColor);
}

void Targetable::setColors(const sf::Color& inSelectedColor, const sf::Color& inNormalColor)
{
	selectedColor = inSelectedColor;
	normalColor = inNormalColor;
}

void Targetable::setHighlighted(bool on)
{
	renderer->setColor(on ? selectedColor : normalColor);
}

