#pragma once
#include "DefaultMove.h"


namespace Game
{
	class EndTurn : public DefaultMove
	{
		public:
			std::unique_ptr<DefaultMove> Clone() const override;
			bool Equals(const DefaultMove* other) const override;
			bool IsValid(const GameState& gameState) const override;
			void ApplyMove(GameState& gameState) const override;
	};
}