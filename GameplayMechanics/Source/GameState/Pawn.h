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
			Pawn(PawnType _unitType, std::shared_ptr<Field> _field);
			PawnType GetUnitType();
			std::unique_ptr<Pawn> Clone() const;
			bool Equals(const Pawn& other) const;
			void PerformAction(GameState& gameState);

		private:
			std::shared_ptr<Field> field;
			const PawnType unitType;
	};
}