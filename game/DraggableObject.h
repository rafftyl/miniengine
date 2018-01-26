#pragma once
#include "Component.h"
#include "InputInterfaces.h"
#include "GameObject.h"

class DraggableObject :	public mini::Component, 
	public mini::input::raycast::IMouseDragHandler,
	public mini::input::raycast::IMouseEnterHandler,
	public mini::input::raycast::IMouseExitHandler
{
private:
	sf::Vector2f offset;	
public:
	DraggableObject(mini::GameObject& owner);
	~DraggableObject();

	// Inherited via IMouseDragHandler
	virtual void onMouseDragStart(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	virtual void onMouseDragEnd(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	virtual void onMouseDrag(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;

	// Inherited via IMouseEnterHandler
	virtual void onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;

	// Inherited via IMouseExitHandler
	virtual void onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};

