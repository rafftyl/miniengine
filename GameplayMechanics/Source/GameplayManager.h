#pragma once
#include <memory>
#include <unordered_map>
#include "GameState\GameState.h"
#include "Players\DefaultPlayer.h"


class GameManager
{
public:
	static GameManager& GetInstance();
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
	void RunGame();
	GameState* GetCurrentGameState();

private:
	GameManager();
	~GameManager();
	std::unique_ptr<GameState> currentGameState;
	std::unordered_map<int, std::unique_ptr<DefaultPlayer>> players;
};