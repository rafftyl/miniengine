#pragma once
#include <vector>
#include <memory>


namespace Game
{
	class Pawn;

	class Field
	{
		public:
			std::unique_ptr<Field> clone() const;
			bool equals(const Field& other) const;

		private:
			std::vector<std::shared_ptr<Pawn>> presentPawns;
	};
}