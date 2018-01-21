#include "stdafx.h"
#include "MouseFollower.h"
#include "GameObject.h"

MouseFollower::MouseFollower(mini::GameObject& owner) : mini::Component(owner)
{
}

MouseFollower::~MouseFollower()
{
}

void MouseFollower::onMouseMove(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.setPosition(mousePosition + offset);
}
