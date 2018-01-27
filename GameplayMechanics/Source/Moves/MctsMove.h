#pragma once
#include <Move.h>


namespace Game
{
	class DefaultMove;
	class GameState;

	class MctsMove : public grailMCTS::Move
	{
		public:
			MctsMove(const DefaultMove* _move);
			std::unique_ptr<grailMCTS::Move> clone() const override;
			bool equals(const grailMCTS::Move& other) const override;
			std::size_t hash() const override;
			std::unique_ptr<const DefaultMove> GetMove();

		private:
			std::unique_ptr<const DefaultMove> move;
	};
}