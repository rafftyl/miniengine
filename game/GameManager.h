#pragma once
#include "Prefab.h"
#include "Scene.h"
#include "GameplaySystem.h"
#include <map>

namespace Game
{
	enum class PawnType;
}

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
	void setupGame(int humanPlayer, mini::Scene& scene, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation);
	void reloadSceneWithNewState(mini::GameplaySystem& gameplaySys, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation);
	void endTurn();
private:
	GameManager();
	~GameManager();
};

