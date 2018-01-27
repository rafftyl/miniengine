#pragma once
#include "Component.h"
#include "Prefab.h"
#include <SFML/System/Vector2.hpp>

class OrderPanel : public mini::Component
{
private:
	sf::Vector2f buttonLayoutOrigin;
	sf::Vector2i buttonLayoutDimensions;
	float buttonSeparation;
	mini::Prefab upArrowPrefab;
	std::vector<mini::GameObject*> spawnedButtons;

	//TODO: spawned abilities
public:
	OrderPanel(mini::GameObject& owner);
	~OrderPanel();
	void start() override;
	void setParams(const sf::Vector2f& origin, const sf::Vector2i& layoutSize, float separation, mini::Prefab upPrefab);
private:
	void initForPawn(const class Pawn& pawn);
};

