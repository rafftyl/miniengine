#pragma once
#include <sstream>
#include <cassert>
#include <memory>


namespace Game
{
	class GameState;
	class Field;

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
			std::unique_ptr<Pawn> clone() const;
			bool equals(const Pawn& other) const;
			void PerformAction(GameState& gameState);

		private:
			std::shared_ptr<Field> field;
			PawnType unitType;
	};
}