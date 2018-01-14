#pragma once
#include "Component.h"
#include "InputInterfaces.h"

class MouseFollower : public mini::Component, public mini::input::IMouseButtonHoldHandler
{
public:
	sf::Vector2f offset{ 0,0 };
public:
	MouseFollower(mini::GameObject& owner);
	~MouseFollower();

	// Inherited via IMouseButtonHoldHandler
	virtual void onMouseButtonHold(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};

