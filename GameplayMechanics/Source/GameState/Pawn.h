#pragma once
#include <sstream>
#include <cassert>
#include <memory>
#include "Field.h"


namespace Game
{
	class GameState;

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

	std::pair<int, int> TranslateDirections(Directions direction)
	{
		std::pair<int, int> result(0, 0);
		switch (direction)
		{
			case Directions::North:
				result.first = -1;
			break;

			case Directions::East:
				result.second = 1;
			break;

			case Directions::South:
				result.first = 1;
			break;

			case Directions::West:
				result.second = -1;
			break;
		}
		return result;
	}
	
	struct PawnActionResult
	{
		//TODO: wrzuci wszystkie potrzebne informacje do animacji
	};

	static std::string GetUnitTypeName(PawnType unitType)
	{
		std::stringstream result;
		switch (unitType)
		{
			case PawnType::Thug:
				result << "Thug";
			break;

			default:
				result << "No designated name for unit type!";
				assert(false && result.str().c_str());
			break;
		}
		return result.str();
	}

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