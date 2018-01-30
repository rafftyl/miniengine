#pragma once
#include <memory>
#include <vector>
#include <list>
#include <valarray>
#include "Field.h"

#define END_GAME -1
#define TURN_LIMIT 20

namespace Game
{
	class Pawn;
	class DefaultMove;
	class EndTurn;
	
	class GameState
	{
		friend EndTurn;
		friend class UnitOrder;

		public:
			std::vector<std::vector<std::shared_ptr<Field>>> board;
			void Initialize();
			std::unique_ptr<GameState> Clone() const;
			bool Equals(const GameState& other) const;
			int PlayersCount() const;
			std::valarray<double> GetResult() const;
			int WhoPlay() const;
			std::vector<std::unique_ptr<const DefaultMove>> GetAllMoves() const;
			bool PerformMove(const DefaultMove& move);
			std::pair<int, int> GetBoardDimensions() const;
			bool AddPawn(std::shared_ptr<Pawn>, std::pair<int, int> coordinates);
			void RemovePawn(std::shared_ptr<Pawn> pawn);
			std::vector<std::shared_ptr<Pawn>> GetPawnsOnCoordinates(std::pair<int, int> coordinates);
			bool IsWon();

			std::list<std::shared_ptr<Pawn>> pawnsOnBoard;
		private:
			int turnCounter;
			int currentPlayer;			
			void TurnEnd();
			void BoardCycle();
	};
}