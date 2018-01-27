#include "Field.h"
#include <list>
#include "Pawn.h"
using namespace Game;


//public
Field::Field(int _capacity) : capacity(_capacity)
{
	presentPawns.reserve(capacity);
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
		return true;
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

std::shared_ptr<Field> Field::Clone() const
{
	std::shared_ptr<Field> result = std::shared_ptr<Field>(new Field(capacity));
	for (auto iterator = presentPawns.begin(); iterator != presentPawns.end(); ++iterator)
	{
		result->presentPawns.push_back(iterator->get()->Clone());
	}
	return result;
}

bool Field::Equals(const Field& other) const
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
			if (ourPawns.front()->Equals(**iterator))
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

int Field::GetCapacity() const
{
	return capacity;
}

std::vector<std::shared_ptr<Pawn>> Field::GetPawns()
{
	return presentPawns;
}

std::vector<std::shared_ptr<const Pawn>> Field::GetPawns() const
{
	std::vector<std::shared_ptr<const Pawn>> result;
	for (const auto& pawn : presentPawns)
	{
		result.push_back(pawn);
	}
	return result;
}


//private