#include "Pawn.h"
#include "GameEvents.h"
#include "GameObject.h"
#include "GameManager.h"

Pawn* Pawn::selectedPawn = nullptr;

Pawn::Pawn(mini::GameObject& owner) : Targetable(owner)
{
}

Pawn::~Pawn()
{
}

void Pawn::start()
{
	Targetable::start();
	GameEvents::getInstance().onPawnSelected.addCallback(
		[&](Pawn& pawn) 
	{
		if (isSelected && this != &pawn) 
		{ 
			isSelected = false;
			renderer->setColor(normalColor);
		}
	});
	
}

void Pawn::setOwnerIndex(int index)
{
	ownerIndex = index;
}

int Pawn::getOwnerIndex() const
{
	return ownerIndex;
}

void Pawn::setHighlighted(bool on)
{
	isSelected = on;
	Targetable::setHighlighted(on);
	if (on)
	{
		GameEvents::getInstance().onPawnSelected.broadcast(*this);
	}
	else
	{
		GameEvents::getInstance().onPawnUnselected.broadcast();
		Pawn::selectedPawn = nullptr;
	}
}

void Pawn::setCurrentField(Field* field)
{
	currentField = field;
}

Field* Pawn::getCurrentField()
{
	return currentField;
}

void Pawn::onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	bool isHumanControlled = ownerIndex == GameManager::getInstance().getCurrentPlayerIndex() && ownerIndex == GameManager::getInstance().getCurrentPlayerIndex();
	if (!isSelected && isHumanControlled && mouseButton == sf::Mouse::Button::Left)
	{	
		selectedPawn = this;
		setHighlighted(true);
	}
}

void Pawn::onMouseButtonPressed(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	if (isSelected && mouseButton == sf::Mouse::Button::Right)
	{
		selectedPawn = nullptr;
		setHighlighted(false);			
	}
}

