#pragma once
#include <Move.h>


namespace Game
{
	class GameState;

	class DefaultMove : public grailMCTS::Move
	{
		public:
			std::unique_ptr<grailMCTS::Move> clone() const override;
			virtual std::unique_ptr<DefaultMove> SpecificClone() const = 0;
			bool equals(const grailMCTS::Move& other) const override;
			virtual bool SpecificEquals(const DefaultMove* other) const = 0;
			std::size_t hash() const override;
			virtual bool IsValid(const GameState& gameState) const = 0;
			virtual void ApplyMove(GameState& gameState) const = 0;
	};
}