#pragma once
#include "Targetable.h"
#include "InputInterfaces.h"
#include "Renderer.h"
#include "Prefab.h"
#include <set>

class Field :
	public Targetable
{
	std::set<class Pawn*> pawns;
	size_t maxPawns;
	mini::Prefab slotPrefab;
	std::vector<mini::GameObject*> slots;
	sf::Vector2i coordinates;
public:
	Field(mini::GameObject& owner);
	void start() override;
	void setCoordinates(const sf::Vector2i& coords);
	sf::Vector2i getCoordinates() const;
	void setSlotPrefab(const mini::Prefab& prefab);
	void setSlotCount(size_t slotCount);
	void addPawn(Pawn* pawn);
	void removePawn(Pawn* pawn);
	void movePawnToField(Pawn* pawn);
};
