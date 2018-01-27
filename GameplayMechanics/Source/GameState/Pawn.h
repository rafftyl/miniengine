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
			bool SetField(std::pair<int, int> _boardCoordinates, GameState& gameState);
			std::pair<int, int> GetBoardCoordinates() const;
			PawnType GetUnitType() const;
			int GetOwner() const;
			std::unique_ptr<Pawn> Clone() const;
			bool Equals(const Pawn& other) const;
			void PerformAction(GameState& gameState);

		private:
			std::pair<int, int> boardCoordinates;
			const PawnType unitType;
			const int owner;
	};
}