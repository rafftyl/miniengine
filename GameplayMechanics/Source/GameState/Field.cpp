#include "Field.h"
#include "Pawn.h"
#include <list>
using namespace Game;


//public
Field::Field(int _capacity) : capacity(_capacity)
{
	presentPawns.resize(capacity);
}

bool Field::InsertPawn(std::shared_ptr<Pawn> pawn)
{
	if (presentPawns.size() < capacity)
	{
		for (auto iterator = presentPawns.begin(); iterator != presentPawns.end(); ++iterator)
		{
			if (iterator->get() == pawn.get())
			{
				return false;
			}
		}
		presentPawns.push_back(pawn);
	}
	else
	{
		return false;
	}
}

bool Field::RemovePawn(std::shared_ptr<Pawn> pawn)
{
	if (presentPawns.size() > 0)
	{
		for (auto iterator = presentPawns.begin(); iterator != presentPawns.end(); ++iterator)
		{
			if (iterator->get() == pawn.get())
			{
				presentPawns.erase(iterator);
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

std::unique_ptr<Field> Field::clone() const
{
	std::unique_ptr<Field> result = std::unique_ptr<Field>();
	for (auto iterator = presentPawns.begin(); iterator != presentPawns.end(); ++iterator)
	{
		result->presentPawns.push_back(iterator->get()->clone());
	}
	return result;
}

bool Field::equals(const Field& other) const
{
	if (presentPawns.size() != other.presentPawns.size())
	{
		return false;
	}
	if (presentPawns.size() == 0)
	{
		return true;
	}
	std::list<Pawn*> ourPawns;
	for (auto iterator = presentPawns.begin(); iterator != presentPawns.end(); ++iterator)
	{
		ourPawns.push_back(iterator->get());
	}
	std::list<Pawn*> theirPawns;
	for (auto iterator = other.presentPawns.begin(); iterator != other.presentPawns.end(); ++iterator)
	{
		theirPawns.push_back(iterator->get());
	}
	bool foundMatch = false;
	while (ourPawns.size() > 0)
	{
		for (auto iterator = theirPawns.begin(); iterator != theirPawns.end(); ++iterator)
		{
			if (ourPawns.front()->equals(**iterator))
			{
				ourPawns.pop_front();
				theirPawns.erase(iterator);
				foundMatch = true;
				break;
			}
		}
		if (!foundMatch)
		{
			return false;
		}
		foundMatch = false;
	}
}


//private