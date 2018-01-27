#pragma once
#include <GameState.h>
#include <Move.h>
#include "GameState.h"


namespace Game
{
	class MctsGameState : public grailMCTS::GameState
	{
		public:
			MctsGameState(Game::GameState* _gameState);
			std::unique_ptr<grailMCTS::GameState> clone() const override;
			bool equals(const grailMCTS::GameState& other) const override;
			std::size_t playersCount() const override;
			grailMCTS::Result getResult() const override;
			int whoPlay() const override;
			std::vector<std::unique_ptr<const grailMCTS::Move>> getMoves() const override;
			void applyMove(const grailMCTS::Move& move) override;
			
		private:
			std::unique_ptr<Game::GameState> gameState;
	};
}