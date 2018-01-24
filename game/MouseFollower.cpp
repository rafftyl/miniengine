#include "stdafx.h"
#include "MouseFollower.h"
#include "GameObject.h"
#include "GameplaySystem.h"

MouseFollower::MouseFollower(mini::GameObject& owner) : mini::Component(owner)
{
}

MouseFollower::~MouseFollower()
{
}

void MouseFollower::onMouseMove(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	sf::Vector2f pos = gameplaySystem->getCurrentCam()->screenToWorldPoint(mousePosition);
	owner.setPosition(pos + offset);
}
