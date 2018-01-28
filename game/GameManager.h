#pragma once
#include "Prefab.h"
#include "Scene.h"
#include "Field.h"
#include "GameplaySystem.h"
#include <map>
#include <set>
#include <thread>

namespace Game
{
	enum class PawnType;
}

class GameManager
{
public:
	std::vector<std::shared_ptr<Field>> fields;
private:
	const int playerCount = 2;
	int currentPlayerIndex = -1;
	std::set<int> humanPlayerIndices;
	std::unique_ptr<std::thread> aiOrderThread;
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	
	int getCurrentPlayerIndex() const;
	bool isHumanPlayer(int index) const;
	bool isCurrentPlayerHuman() const;
	void setupGame(std::set<int> humanPlayers, mini::Scene& scene, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation);
	void reloadSceneWithNewState(mini::GameplaySystem& gameplaySys, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation);
	void endTurn(bool requestAIMove = true);
private:
	GameManager();
	~GameManager();
};

