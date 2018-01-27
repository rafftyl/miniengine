#include "Pawn.h"
#include "..\GameState\GameState.h"
#include "Field.h"
using namespace Game;


//public
Pawn::Pawn(PawnType _unitType, int _owner) : unitType(_unitType), owner(_owner)
{
	boardCoordinates.first = -1;
	boardCoordinates.second = -1;
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
}

bool Pawn::SetField(std::pair<int, int> _boardCoordinates, GameState& gameState)
{
	boardCoordinates = _boardCoordinates;
	return true;
}

std::pair<int, int> Pawn::GetBoardCoordinates() const
{
	return boardCoordinates;
}

PawnType Pawn::GetUnitType() const
{
	return unitType;
}

int Pawn::GetOwner() const
{
	return owner;
}

std::unique_ptr<Pawn> Pawn::Clone() const
{
	std::unique_ptr<Pawn> copy = std::unique_ptr<Pawn>(new Pawn(unitType, owner));
	copy->boardCoordinates.first = boardCoordinates.first;
	copy->boardCoordinates.second = boardCoordinates.second;
	return copy;
}

bool Pawn::Equals(const Pawn& other) const
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