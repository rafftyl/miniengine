#pragma once
#include <memory>
#include <list>
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
			std::list<std::unique_ptr<DefaultMove>> GetMovesToAnimate();

		private:
			std::unique_ptr<GameState> currentGameState;
			std::list<std::unique_ptr<DefaultMove>> movesToAnimate;
			grailMCTS::MCTS mcts;
			void Initialize();
			GameplayManager();
			~GameplayManager();
	};
}