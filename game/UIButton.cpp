#include "UIButton.h"
#include "GameObject.h"

UIButton::UIButton(mini::GameObject& owner) : Component(owner)
{
}

UIButton::~UIButton()
{
}

ButtonEvent& UIButton::onClicked()
{
	return onClickedEvent;
}

ButtonEvent& UIButton::onMouseEnter()
{
	return onMouseEnterEvent;
}

ButtonEvent& UIButton::onMouseExit()
{
	return onMouseExitEvent;
}

void UIButton::start()
{
	collider = owner.getComponent<mini::Collider>();
	if (collider == nullptr)
	{
		collider = owner.addComponent<mini::BoxCollider>();
	}
}

void UIButton::onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	isPressed = true;
}

void UIButton::onMouseButtonReleased(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	if (isPressed)
	{
		isPressed = false;
		if (collider->contains(mousePosition))
		{
			onClickedEvent.broadcast(*this);
		}
	}
}

void UIButton::onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	onMouseEnterEvent.broadcast(*this);
}

void UIButton::onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	onMouseExitEvent.broadcast(*this);
}
