#include "DefaultMove.h"
using namespace Game;


//public
std::unique_ptr<grailMCTS::Move> DefaultMove::clone() const
{
	std::unique_ptr<grailMCTS::Move> copy = std::unique_ptr<grailMCTS::Move>();
	return copy;
}

bool DefaultMove::equals(const grailMCTS::Move& other) const
{
	const DefaultMove* temp = dynamic_cast<const DefaultMove*>(&other);
	if (temp != nullptr)
	{
		return true;
	}
	return false;
}

std::size_t DefaultMove::hash() const
{
	return 0;
}