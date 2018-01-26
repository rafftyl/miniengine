#include "stdafx.h"
#include "DraggableObject.h"
#include "Renderer.h"
#include "GameplaySystem.h"

DraggableObject::DraggableObject(mini::GameObject& owner) : Component(owner)
{
}


DraggableObject::~DraggableObject()
{
}

void DraggableObject::onMouseDragStart(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	sf::Vector2f pos = owner.isScreenSpace() ? mousePosition : gameplaySystem->getCurrentCam()->screenToWorldPoint(mousePosition);
	offset = owner.getPosition() - pos;
}

void DraggableObject::onMouseDragEnd(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
}

void DraggableObject::onMouseDrag(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	sf::Vector2f pos = owner.isScreenSpace() ? mousePosition : gameplaySystem->getCurrentCam()->screenToWorldPoint(mousePosition);
	owner.setPosition(pos + offset);
}

void DraggableObject::onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.getComponent<mini::Renderer>()->setColor(sf::Color::Green);
}

void DraggableObject::onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	owner.getComponent<mini::Renderer>()->setColor(sf::Color::Red);
}
