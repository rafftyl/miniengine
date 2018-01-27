#include "UnitOrder.h"
#include "..\GameState\GameState.h"
using namespace Game;

UnitOrder::UnitOrder(std::shared_ptr<Pawn> _targetPawn, OrderType _orderType, Directions _direction) : targetPawn(_targetPawn), orderType(_orderType), direction(_direction)
{
}

std::unique_ptr<DefaultMove> UnitOrder::Clone() const
{
	std::unique_ptr<UnitOrder> result = std::unique_ptr<UnitOrder>(new UnitOrder(targetPawn, orderType, direction));
	return result;
}

bool UnitOrder::Equals(const DefaultMove* other) const
{
	const UnitOrder* temp = dynamic_cast<const UnitOrder*>(other);
	if (temp != nullptr)
	{
		if (targetPawn.get() == temp->targetPawn.get() && orderType == temp->orderType && direction == temp->direction)
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
	targetPawn->SetNewOrder(orderType, direction);
}