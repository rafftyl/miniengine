#pragma once
#include <memory>
#include <list>
#include <functional>

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
			GameState& GetCurrentGameState();
			void RestartGame();
			void AI_PerformTurn();
			std::function<void(const std::list<std::unique_ptr<const DefaultMove>>&)> onAnimationQueueCreated;
			std::function<void(GameState&)> onNewGameStateFound;
		private:
			std::unique_ptr<grailMCTS::MCTS> mcts;
			std::unique_ptr<GameState> currentGameState;
			std::list<std::unique_ptr<const DefaultMove>> movesToAnimate;
			GameplayManager();
			~GameplayManager();
	};
}