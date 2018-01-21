#include "stdafx.h"
#include "DraggableObject.h"
#include "Renderer.h"

DraggableObject::DraggableObject(mini::GameObject& owner) : Component(owner)
{
}


DraggableObject::~DraggableObject()
{
}

void DraggableObject::onMouseDragStart(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	offset = owner.getPosition() - mousePosition;
}

void DraggableObject::onMouseDragEnd(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
}

void DraggableObject::onMouseDrag(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.setPosition(mousePosition + offset);
}

void DraggableObject::onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.getComponent<mini::Renderer>()->setColor(sf::Color::Green);
}

void DraggableObject::onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.getComponent<mini::Renderer>()->setColor(sf::Color::Red);
}
