#pragma once
#include <Move.h>


namespace Game
{
	class GameState;

	class DefaultMove : public grailMCTS::Move
	{
		public:
			std::unique_ptr<grailMCTS::Move> clone() const override;
			bool equals(const grailMCTS::Move& other) const override;
			std::size_t hash() const override;
			virtual bool IsValid(const GameState& gameState) const = 0;
			virtual void ApplyMove(GameState& gameState) const = 0;
	};
}