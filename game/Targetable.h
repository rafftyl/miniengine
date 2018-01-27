#pragma once
#include "Component.h"
#include "Renderer.h"

class Targetable : public mini::Component
{
protected:
	std::shared_ptr<mini::Renderer> renderer;
	sf::Color selectedColor;
	sf::Color normalColor;
public:
	Targetable(mini::GameObject& owner);
	~Targetable();

	void start() override;
	void setColors(const sf::Color& inSelectedColor, const sf::Color& inNormalColor);
	virtual void setHighlighted(bool on);
};

