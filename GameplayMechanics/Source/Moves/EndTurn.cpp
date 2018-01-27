#include "EndTurn.h"
#include "..\GameState\GameState.h"
using namespace Game;

//public
std::unique_ptr<DefaultMove> EndTurn::SpecificClone() const
{
	return std::unique_ptr<DefaultMove>(new EndTurn());
}

bool EndTurn::SpecificEquals(const DefaultMove* other) const
{
	const EndTurn* temp = dynamic_cast<const EndTurn*>(other);
	if (temp != nullptr)
	{
		return true;
	}
	return false;
}

bool EndTurn::IsValid(const GameState& gameState) const
{
	if (gameState.whoPlay() != grailMCTS::TERMINAL)
	{
		return true;
	}
	return false;
}

void EndTurn::ApplyMove(GameState& gameState) const
{

}


//private