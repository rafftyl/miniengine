#include "stdafx.h"
#include "KeyMover.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"

KeyMover::KeyMover(mini::GameObject& owner) : Component(owner)
{
}

KeyMover::~KeyMover()
{
}

void KeyMover::onKeyHold(sf::Keyboard::Key key, const mini::ModifierKeys& modifiers)
{
	switch (key)
	{
	case sf::Keyboard::D:
		owner.move(sf::Vector2f(150, 0) * mini::Time::getDeltaTime());
		break;
	case sf::Keyboard::A:
		owner.move(sf::Vector2f(-150, 0) * mini::Time::getDeltaTime());
		break;
	case sf::Keyboard::W:
		owner.move(sf::Vector2f(0, -150) * mini::Time::getDeltaTime());
		break;
	case sf::Keyboard::S:
		owner.move(sf::Vector2f(0, 150) * mini::Time::getDeltaTime());
		break;
	default:
		break;
	}
}

void KeyMover::onMouseWheel(float delta)
{
	auto cam = owner.getComponent<mini::Camera>();
	sf::Vector2f orthoSize = cam->getOrthoSize();
	float aspect = orthoSize.x / orthoSize.y;
	cam->setOrthoSize(orthoSize + sf::Vector2f(10 * delta * aspect, 10 * delta));
}
