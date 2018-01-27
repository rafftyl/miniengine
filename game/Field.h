#pragma once
#include "Targetable.h"
#include "InputInterfaces.h"
#include "Renderer.h"
#include "Prefab.h"
#include <set>

class Field :
	public Targetable,
	public mini::input::IMouseButtonPressHandlerRaycast
{
	std::set<class Pawn*> pawns;
	size_t maxPawns;
	mini::Prefab slotPrefab;
	std::vector<mini::GameObject*> slots;
public:
	Field(mini::GameObject& owner);
	~Field();
	void start() override;
	void setSlotPrefab(const mini::Prefab& prefab);
	void setSlotCount(size_t slotCount);
	void addPawn(Pawn* pawn);
	void removePawn(Pawn* pawn);
	virtual void onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};
