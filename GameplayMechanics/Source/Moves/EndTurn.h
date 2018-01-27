#pragma once
#include "DefaultMove.h"


namespace Game
{
	class EndTurn : public DefaultMove
	{
		public:
			std::unique_ptr<DefaultMove> SpecificClone() const override;
			bool SpecificEquals(const DefaultMove* other) const override;
			bool IsValid(const GameState& gameState) const override;
			void ApplyMove(GameState& gameState) const override;
	};
}