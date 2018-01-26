#pragma once
#include <memory>
#include <unordered_map>
#include "GameState\GameState.h"
#include "Players\DefaultPlayer.h"


class GameplayManager
{
public:
	GameplayManager(GameplayManager const&) = delete;
	void operator=(GameplayManager const&) = delete;
	static GameplayManager& GetInstance();
	void RunGame();
	GameState* GetCurrentGameState();

private:
	std::unique_ptr<GameState> currentGameState;
	std::unordered_map<int, std::unique_ptr<DefaultPlayer>> players;
	GameplayManager();
	~GameplayManager();
};