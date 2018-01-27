#include "Field.h"
#include <list>
#include "Pawn.h"
using namespace Game;


//public
Field::Field(int _capacity) : capacity(_capacity)
{
}

std::shared_ptr<Field> Field::Clone() const
{
	std::shared_ptr<Field> result = std::shared_ptr<Field>(new Field(capacity));
	result->slotsTaken = slotsTaken;
	return result;
}

bool Field::Equals(const Field& other) const
{
	if (capacity == other.capacity && slotsTaken == other.slotsTaken)
	{
		return true;
	}
	return false;
}

int Field::GetCapacity() const
{
	return capacity;
}


//private