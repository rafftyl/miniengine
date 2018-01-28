#pragma once
#include "DefaultMove.h"
#include "..\GameState\Pawn.h"


namespace Game
{
	class UnitOrder : public DefaultMove
	{
		public:
			UnitOrder(Pawn* _targetPawn, OrderType _orderType, Directions _direction);
			std::unique_ptr<DefaultMove> Clone() const override;
			bool Equals(const DefaultMove* other) const override;
			bool IsValid(const GameState& gameState) const override;
			void ApplyMove(GameState& gameState) const override;

		private:
			Pawn* targetPawn;
			const OrderType orderType;
			const Directions direction;
	};
}