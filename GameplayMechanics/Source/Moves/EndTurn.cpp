#include "EndTurn.h"
#include "..\GameState\GameState.h"
using namespace Game;

//public
std::unique_ptr<DefaultMove> EndTurn::clone() const
{
	return std::unique_ptr<DefaultMove>(new EndTurn());
}

bool EndTurn::equals(const DefaultMove* other) const
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
	if (gameState.WhoPlay() >= 0)
	{
		return true;
	}
	return false;
}

void EndTurn::ApplyMove(GameState& gameState) const
{

}


//private