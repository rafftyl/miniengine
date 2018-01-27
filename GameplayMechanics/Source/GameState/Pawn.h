#pragma once
#include <sstream>
#include <cassert>
#include <memory>


namespace Game
{
	enum class PawnType
	{
		Thug, Max
	};

	std::string GetUnitTypeName(PawnType unitType)
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
			Pawn(PawnType _unitType);
			std::unique_ptr<Pawn> clone() const;
			bool equals(const Pawn& other) const;

		private:
			PawnType unitType;
	};
}