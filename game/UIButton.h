#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "InputInterfaces.h"
#include "Event.h"

typedef mini::Event<class UIButton&> ButtonEvent;
class UIButton :
	public mini::Component, 
	public mini::input::raycast::IMouseButtonPressHandler,
	public mini::input::IMouseButtonReleaseHandler,
	public mini::input::raycast::IMouseEnterHandler,
	public mini::input::raycast::IMouseExitHandler
{	
private:
	ButtonEvent onClickedEvent;
	ButtonEvent onMouseEnterEvent;
	ButtonEvent onMouseExitEvent;
	std::shared_ptr<mini::Collider> collider;
	bool isPressed = false;
public: 
	UIButton(mini::GameObject& owner);
	~UIButton();

	ButtonEvent& onClicked();
	ButtonEvent& onMouseEnter();
	ButtonEvent& onMouseExit();

	virtual void start() override;

	virtual void onMouseButtonPressed(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	virtual void onMouseButtonReleased(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	virtual void onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	virtual void onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};

