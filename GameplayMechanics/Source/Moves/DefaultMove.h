#pragma once
#include <Move.h>


namespace Game
{
	class DefaultMove : public grailMCTS::Move
	{
		public:
			std::unique_ptr<grailMCTS::Move> clone() const override;
			bool equals(const grailMCTS::Move& other) const override;
			std::size_t hash() const override;
	};
}