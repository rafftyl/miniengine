#pragma once
#include "Prefab.h"
#include "Scene.h"

class GameManager
{
private:
	const int playerCount = 2;
	int currentPlayerIndex = -1;
	int humanPlayerIndex = -1;
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	
	int getCurrentPlayerIndex() const;
	int getHumanPlayerIndex() const;
	bool isCurrentPlayerHuman() const;
	void setupGame(int humanPlayer, mini::Scene& scene, mini::Prefab& fieldPrefab, std::vector<size_t> fieldCapacities, int cols, const sf::Vector2f& origin, float fieldSeparation);
	void endTurn();
private:
	GameManager();
	~GameManager();
};

