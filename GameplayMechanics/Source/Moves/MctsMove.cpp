#include "MctsMove.h"
#include "DefaultMove.h"
using namespace Game;


//public
MctsMove::MctsMove(const DefaultMove* _move)
{
	move = std::unique_ptr<const DefaultMove>(_move);
}

std::unique_ptr<grailMCTS::Move> MctsMove::clone() const
{
	std::unique_ptr<grailMCTS::Move> copy = std::unique_ptr<MctsMove>(new MctsMove(move->Clone().release()));
	return copy;
}

bool MctsMove::equals(const grailMCTS::Move& other) const
{
	const MctsMove* temp = dynamic_cast<const MctsMove*>(&other);
	if (temp != nullptr)
	{
		if (!move->Equals(temp->move.get()))
		{
			return false;
		}
		return true;
	}
	return false;
}

std::size_t MctsMove::hash() const
{
	return 0;
}

std::unique_ptr<const DefaultMove> MctsMove::GetMove()
{
	return std::move(move);
}