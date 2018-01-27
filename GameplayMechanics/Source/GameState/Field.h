#pragma once
#include <vector>
#include <memory>


namespace Game
{
	class Pawn;

	class Field
	{
		public:
			Field(int _capacity);
			bool InsertPawn(std::shared_ptr<Pawn> pawn);
			bool RemovePawn(std::shared_ptr<Pawn> pawn);
			std::unique_ptr<Field> clone() const;
			bool equals(const Field& other) const;
			int GetCapacity() const;
			std::vector<std::shared_ptr<Pawn>> GetPawns();
			std::vector<std::shared_ptr<const Pawn>> GetPawns() const;

		private:
			const int capacity;
			std::vector<std::shared_ptr<Pawn>> presentPawns;
	};
}