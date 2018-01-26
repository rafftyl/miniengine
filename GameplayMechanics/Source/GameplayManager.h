#pragma once
#include <mutex>
#include <memory>
#include <unordered_map>
#include <MCTS.h>
#include "GameState\GameState.h"


namespace Game
{
	class GameplayManager
	{
	public:
		GameplayManager(GameplayManager const&) = delete;
		void operator=(GameplayManager const&) = delete;
		static GameplayManager& GetInstance();
		const GameState& GetCurrentGameState() const;
		void RestartGame();
		bool AI_PerformTurn();

	private:
		grailMCTS::MCTS mcts;
		std::unique_ptr<GameState> currentGameState;
		void Initialize();
		GameplayManager();
		~GameplayManager();
	};
}