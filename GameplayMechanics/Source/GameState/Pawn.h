#pragma once
#include <sstream>
#include <cassert>
#include <memory>
#include "GameState.h"


namespace Game
{
	enum class PawnType
	{
		Thug, Max
	};

	enum class OrderType
	{
		Stop, Advance, Max
	};

	enum class Directions
	{
		North, East, South, West
	};

	std::pair<int, int> TranslateDirections(Directions direction);
	
	struct PawnActionResult
	{
		//TODO: wrzuci wszystkie potrzebne informacje do animacji
	};

	static std::string GetUnitTypeName(PawnType unitType);

	class Pawn
	{
		public:
			Pawn(PawnType _unitType, int _owner);
			void SetBoardCoordinates(std::pair<int, int> newCoordinates);
			std::pair<int, int> GetBoardCoordinates() const;
			PawnType GetUnitType() const;
			int GetOwner() const;
			std::unique_ptr<Pawn> Clone() const;
			bool Equals(const Pawn& other) const;
			void SetNewOrder(OrderType newOrder, Directions newDirections);
			PawnActionResult PerformAction(GameState& gameState);
			void ChangeHealth(int ammount);

		private:
			std::pair<int, int> boardCoordinates;
			const PawnType unitType;
			OrderType lastOrder;
			Directions direction;
			const int owner;
			int health;
			int maxHealth;
			int speed;
			int meeleAttack;
			PawnActionResult Stop(GameState& gameState);
			PawnActionResult Advance(GameState& gameState);
			bool Fight(GameState& gameState, PawnActionResult& result);
			bool Move(GameState& gameState, PawnActionResult& result);
			std::shared_ptr<Pawn> FindTarget(GameState& gameState);
	};
}