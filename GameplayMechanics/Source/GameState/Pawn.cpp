#include "Pawn.h"
#include "..\GameState\GameState.h"
#include "..\Moves\UnitOrder.h"
#include "Field.h"
using namespace Game;


//public
Pawn::Pawn(PawnType _unitType, int _owner) : unitType(_unitType), owner(_owner)
{
	boardCoordinates.first = -1;
	boardCoordinates.second = -1;
	lastOrder = OrderType::Stop;
	direction = Directions::North;
	health = maxHealth;
	switch (_unitType)
	{
		case PawnType::Thug:
			maxHealth = 3;
			speed = 2;
			meeleAttack = 2;
		break;

		default:
			std::stringstream stream;
			stream << "Missing constructor implementation for pawn type: " << GetUnitTypeName(_unitType);
			assert(false && stream.str().c_str());
		break;
	}
}

void Pawn::SetBoardCoordinates(std::pair<int, int> newCoordinates)
{
	boardCoordinates = newCoordinates;
}

std::pair<int, int> Pawn::GetBoardCoordinates() const
{
	return boardCoordinates;
}

PawnType Pawn::GetUnitType() const
{
	return unitType;
}

int Pawn::GetOwner() const
{
	return owner;
}

int Pawn::GetHealth() const
{
	return health;
}

int Pawn::GetMaxHealth() const
{
	return maxHealth;
}

std::unique_ptr<Pawn> Pawn::Clone() const
{
	std::unique_ptr<Pawn> copy = std::unique_ptr<Pawn>(new Pawn(unitType, owner));
	copy->boardCoordinates = boardCoordinates;
	copy->lastOrder = lastOrder;
	copy->direction = direction;
	copy->health = health;
	return copy;
}

bool Pawn::Equals(const Pawn& other) const
{
	if (unitType != other.unitType || health != other.health || lastOrder != other.lastOrder || direction != other.direction || boardCoordinates != other.boardCoordinates)
	{
		return false;
	}
	return true;
}

void Pawn::SetNewOrder(OrderType newOrder, Directions newDirection)
{
	lastOrder = newOrder;
	direction = newDirection;
}

PawnActionResult Pawn::PerformAction(GameState& gameState)
{
	switch (lastOrder)
	{
		case OrderType::Stop:
			return Stop(gameState);
		break;

		case OrderType::Advance:
			return Advance(gameState);
		break;

		default:
			assert(false && "Missing action implementation for order!");
		break;
	}
}

void Pawn::ChangeHealth(int ammount)
{
	health += ammount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

std::vector<UnitOrder*> Pawn::GetAvailableOrders(const GameState& gameState)
{
	std::vector<UnitOrder*> result;
	if (lastOrder != OrderType::Stop)
	{
		result.push_back(new UnitOrder(this, OrderType::Stop, Directions::North));
	}

	for (int type = 1; type < static_cast<int>(OrderType::Max); ++type)
	{
		for (int dir = 0; dir < static_cast<int>(Directions::Max); ++dir)
		{
			if (boardCoordinates.first + TranslateDirections(static_cast<Directions>(dir)).first >= 0 &&
				boardCoordinates.first + TranslateDirections(static_cast<Directions>(dir)).first < gameState.GetBoardDimensions().first &&
				boardCoordinates.second + TranslateDirections(static_cast<Directions>(dir)).second >= 0 &&
				boardCoordinates.second + TranslateDirections(static_cast<Directions>(dir)).second < gameState.GetBoardDimensions().second)
			{
				if (static_cast<OrderType>(type) != lastOrder || direction != static_cast<Directions>(dir))
				{
					result.push_back(new UnitOrder(this, static_cast<OrderType>(type), static_cast<Directions>(dir)));
				}
			}
		}
	}
	return result;
}


//private
PawnActionResult Pawn::Stop(GameState& gameState)
{	
	PawnActionResult result = PawnActionResult();
	//TODO: efect stop do result
	return result;
}

PawnActionResult Pawn::Advance(GameState& gameState)
{
	PawnActionResult result = PawnActionResult();
	if (Fight(gameState, result))
	{
	}
	else if (Move(gameState, result))
	{
	}
	else
	{
		//TODO: efect stop do result
	}
	return result;
}

bool Pawn::Fight(GameState& gameState, PawnActionResult& result)
{
	std::shared_ptr<Pawn> target = FindTarget(gameState);
	if (target != nullptr)
	{
		//TODO: efekt ataku do result
		target->ChangeHealth(-meeleAttack);
		if (target->health <= 0)
		{
			gameState.RemovePawn(std::shared_ptr<Pawn>(target));
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Pawn::Move(GameState& gameState, PawnActionResult& result)
{
	std::pair<int, int> nextField(boardCoordinates.first + TranslateDirections(direction).first, boardCoordinates.second + TranslateDirections(direction).second);
	if (nextField.first >= 0 && nextField.first < gameState.GetBoardDimensions().first && nextField.second >= 0 && nextField.second < gameState.GetBoardDimensions().second)
	{
		if (gameState.board[nextField.first][nextField.second]->slotsTaken < gameState.board[nextField.first][nextField.second]->GetCapacity())
		{
			boardCoordinates = nextField;
			++gameState.board[nextField.first][nextField.second]->slotsTaken;
			return true;
		}
	}
	return false;
}

std::shared_ptr<Pawn> Pawn::FindTarget(GameState& gameState)
{
	std::vector<std::shared_ptr<Pawn>> pawns = gameState.GetPawnsOnCoordinates(boardCoordinates);
	std::shared_ptr<Pawn> target = std::shared_ptr<Pawn>(nullptr);
	for (auto iterator = pawns.begin(); iterator != pawns.end(); ++iterator)
	{
		if (iterator->get()->GetOwner() != owner)
		{
			target = *iterator;
			break;
		}
	}
	return target;
}

std::pair<int, int> Game::TranslateDirections(Directions direction)
{
	std::pair<int, int> result(0, 0);
	switch (direction)
	{
	case Directions::North:
		result.first = -1;
		break;

	case Directions::East:
		result.second = 1;
		break;

	case Directions::South:
		result.first = 1;
		break;

	case Directions::West:
		result.second = -1;
		break;
	}
	return result;
}

std::string Game::GetUnitTypeName(PawnType unitType)
{
	std::stringstream result;
	switch (unitType)
	{
	case PawnType::Thug:
		result << "Thug";
		break;

	default:
		result << "No designated name for unit type!";
		assert(false && result.str().c_str());
		break;
	}
	return result.str();
}
