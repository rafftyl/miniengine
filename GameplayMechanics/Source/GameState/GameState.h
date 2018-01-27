#pragma once
#include <memory>
#include <vector>
#define END_GAME -1


namespace Game
{
	class Field;
	class Pawn;
	class DefaultMove;
	class EndTurn;
	
	class GameState
	{
		friend EndTurn;

		public:
			GameState();
			std::unique_ptr<GameState> Clone() const;
			bool Equals(const GameState& other) const;
			int PlayersCount() const;
			std::vector<double> GetResult() const;
			int WhoPlay() const;
			std::vector<std::unique_ptr<const DefaultMove>> GetAllMoves() const;
			bool PerformMove(const DefaultMove& move);
			std::pair<int, int> GetBoardDimensions() const;
			std::shared_ptr<const Field> GetField(int row, int column) const;

		private:
			int currentPlayer;
			std::vector<std::vector<std::shared_ptr<Field>>> board;
			std::vector<std::shared_ptr<Pawn>> unitsOnBoard;
			void TurnEnd();
			void BoardCycle();
			bool IsWon();
	};
}