#pragma once
#include <memory>


namespace Game
{
	class Pawn;

	class Field
	{
		public:
			Field(int _capacity);
			std::shared_ptr<Field> Clone() const;
			bool Equals(const Field& other) const;
			int GetCapacity() const;
			int slotsTaken = 0;

		private:
			const int capacity;
	};
}