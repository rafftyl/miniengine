#include "UnitOrder.h"
#include "..\GameState\GameState.h"
using namespace Game;

UnitOrder::UnitOrder(Pawn* _targetPawn, int _pawnIndex, OrderType _orderType, Directions _direction) : targetPawn(_targetPawn), pawnIndex(_pawnIndex), orderType(_orderType), direction(_direction)
{
}

std::unique_ptr<DefaultMove> UnitOrder::Clone() const
{
	std::unique_ptr<UnitOrder> result = std::unique_ptr<UnitOrder>(new UnitOrder(targetPawn, pawnIndex, orderType, direction));
	return result;
}

bool UnitOrder::Equals(const DefaultMove* other) const
{
	const UnitOrder* temp = dynamic_cast<const UnitOrder*>(other);
	if (temp != nullptr)
	{
		if (targetPawn == temp->targetPawn && orderType == temp->orderType && direction == temp->direction)
		{
			return true;
		}
	}
	return false;
}

bool UnitOrder::IsValid(const GameState& gameState) const
{
	return true;
}

void UnitOrder::ApplyMove(GameState& gameState) const
{
	auto iter = gameState.pawnsOnBoard.begin();
	for (int i = 0; i < pawnIndex; ++i)
	{
		++iter;
	}
	targetPawn = iter->get();
	targetPawn->SetNewOrder(orderType, direction);
	gameState.TurnEnd();
}