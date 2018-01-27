#pragma once
#include <memory>


namespace Game
{
	class GameState;

	class DefaultMove
	{
		public:
			virtual std::unique_ptr<DefaultMove> clone() const = 0;
			virtual bool equals(const DefaultMove* other) const = 0;
			virtual bool IsValid(const GameState& gameState) const = 0;
			virtual void ApplyMove(GameState& gameState) const = 0;
			int Hash() const;
	};
}