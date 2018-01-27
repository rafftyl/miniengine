#pragma once
#include <memory>
#include <list>

namespace grailMCTS
{
	class MCTS;
}

namespace Game
{
	
	class GameState;
	class DefaultMove;

	class GameplayManager
	{
		public:
			GameplayManager(GameplayManager const&) = delete;
			void operator=(GameplayManager const&) = delete;
			static GameplayManager& GetInstance();
			const GameState& GetCurrentGameState() const;
			void RestartGame();
			bool AI_PerformTurn();
			std::list<std::unique_ptr<const DefaultMove>> GetMovesToAnimate();

		private:
			std::unique_ptr<grailMCTS::MCTS> mcts;
			std::unique_ptr<GameState> currentGameState;
			std::list<std::unique_ptr<const DefaultMove>> movesToAnimate;
			void Initialize();
			GameplayManager();
			~GameplayManager();
	};
}