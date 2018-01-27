#pragma once
#include <unordered_map>
#include <GameState.h>
#include <Move.h>


namespace Game
{
	class Field;
	class DefaultMove;
	class EndTurn;

	class GameState : public grailMCTS::GameState
	{
		friend EndTurn;

		public:
			GameState();
			std::unique_ptr<grailMCTS::GameState> clone() const override;
			bool equals(const grailMCTS::GameState& other) const override;
			std::size_t playersCount() const override;
			grailMCTS::Result getResult() const override;
			int whoPlay() const override;
			std::vector<std::unique_ptr<const grailMCTS::Move>> getMoves() const override;
			void applyMove(const grailMCTS::Move& move) override;
			bool PerformMove(const DefaultMove& move);

		private:
			int currentPlayer;
			std::vector<std::vector<std::unique_ptr<Field>>> board;
			std::unordered_map<int, std::vector<std::shared_ptr<Pawn>>> unitsByInitiative;
			void TurnEnd();
			void BoardCycle();
			bool IsWon();
	};
}