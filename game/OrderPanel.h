#pragma once
#include "Component.h"
#include "Prefab.h"
#include "Moves/DefaultMove.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

class OrderPanel : public mini::Component
{
private:
	sf::Vector2f buttonLayoutOrigin;
	sf::Vector2i buttonLayoutDimensions;
	float buttonSeparation;
	mini::Prefab upArrowPrefab;
	mini::Prefab stopButtonPrefab;
	std::vector<mini::GameObject*> spawnedButtons;
	std::vector<std::unique_ptr<const Game::DefaultMove>> filteredMoves;
public:
	OrderPanel(mini::GameObject& owner);
	~OrderPanel();
	void start() override;
	void setParams(const sf::Vector2f& origin, const sf::Vector2i& layoutSize, float separation, mini::Prefab upPrefab, mini::Prefab stopPrefab);
private:
	void initForPawn(const class Pawn& pawn);
};

