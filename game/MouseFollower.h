#pragma once
#include "Component.h"
#include "InputInterfaces.h"

class MouseFollower : public mini::Component, public mini::input::IMouseMoveHandler
{
public:
	sf::Vector2f offset{ 0,0 };
public:
	MouseFollower(mini::GameObject& owner);
	~MouseFollower();

	// Inherited via IMouseButtonHoldHandler
	virtual void onMouseMove(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};

