#include "Pawn.h"
#include "..\GameState\GameState.h"
using namespace Game;


//public
Pawn::Pawn(PawnType _unitType)
{
	switch (_unitType)
	{
		case PawnType::Thug:
			
		break;

		default:
			std::stringstream stream;
			stream << "Missing constructor implementation for pawn type: " << GetUnitTypeName(_unitType);
			assert(false && stream.str().c_str());
		break;
	}
	unitType = _unitType;
}

std::unique_ptr<Pawn> Pawn::clone() const
{
	std::unique_ptr<Pawn> copy = std::unique_ptr<Pawn>(new Pawn(unitType));
	return copy;
}

bool Pawn::equals(const Pawn& other) const
{
	if (unitType != other.unitType)
	{
		return false;
	}
	return true;
}

void Pawn::PerformAction(GameState& gameState)
{
}


//private