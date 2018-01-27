#include "Field.h"
#include "GameObject.h"
#include "Pawn.h"
#include "PositionInterpolator.h"
#include "GameplaySystem.h"

Field::Field(mini::GameObject& owner) : Targetable(owner)
{
}

Field::~Field()
{
}

void Field::start()
{
	sf::Vector2f min, max;
	owner.getComponent<mini::Renderer>()->getBounds(min, max);
	sf::Vector2f slotSeparation = 0.5f * (max - min);
	for (size_t i = 0; i < maxPawns; ++i)
	{
		size_t row = i / 2;
		size_t col = i - row * 2;
		auto& slot = slotPrefab.instantiate(getGameplaySystem().getCurrentScene());
		sf::Vector2f pos(min.x +  slotSeparation.x * (col + 0.5f), min.y +  slotSeparation.y * (row + 0.5f));
		slot.setPosition(pos);
		slots.push_back(&slot);
	}
}

void Field::setCoordinates(const sf::Vector2i& coords)
{
	coordinates = coords;
}

sf::Vector2i Field::getCoordinates() const
{
	return coordinates;
}

void Field::setSlotPrefab(const mini::Prefab& prefab)
{
	slotPrefab = prefab;
}

void Field::setSlotCount(size_t slotCount)
{
	maxPawns = slotCount;
}

void Field::addPawn(Pawn* pawn)
{
	pawns.insert(pawn);
}

void Field::removePawn(Pawn* pawn)
{
	pawns.erase(pawn);
	int index = 0;
	for (auto remaining : pawns)
	{
		std::queue<std::pair<float, sf::Vector2f>> movementQueue;
		movementQueue.push({ 1.0f, slots[index]->getPosition() });
		remaining->getOwner().getComponent<PositionInterpolator>()->startMovement(std::move(movementQueue));
		index++;
	}
}

void Field::onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	if (Pawn::selectedPawn != nullptr && pawns.size() < maxPawns && pawns.find(Pawn::selectedPawn) == pawns.end())
	{
		if (Pawn::selectedPawn->getCurrentField() != nullptr)
		{
			Pawn::selectedPawn->getCurrentField()->removePawn(Pawn::selectedPawn);
		}
		addPawn(Pawn::selectedPawn);
		Pawn::selectedPawn->setCurrentField(this);

		std::queue<std::pair<float, sf::Vector2f>> movementQueue;
		movementQueue.push({ 1.0f, slots[pawns.size() - 1]->getPosition() });
		Pawn::selectedPawn->getOwner().getComponent<PositionInterpolator>()->startMovement(std::move(movementQueue));
		
		Pawn::selectedPawn->setHighlighted(false);
	}
}
