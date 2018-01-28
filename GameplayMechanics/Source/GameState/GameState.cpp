#include "GameState.h"
#include <cassert>
#include "Field.h"
#include "Pawn.h"
#include "..\Moves\DefaultMove.h"
#include "..\Moves\EndTurn.h"
#include "..\Moves\UnitOrder.h"
using namespace Game;


//public
void GameState::Initialize()
{
	//TODO: przeniesienie konstrukcji planszy
	currentPlayer = 0;
	turnCounter = 0;
	board = std::vector<std::vector<std::shared_ptr<Field>>>();
	board.reserve(4);
	for (int row = 0; row < 4; ++row)
	{
		board.push_back(std::vector<std::shared_ptr<Field>>());
		board[row].reserve(5);
		for (int column = 0; column < 5; ++column)
		{
			board[row].push_back(std::make_shared<Field>(4));
		}
	}
	std::shared_ptr<Pawn> newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 0));
	AddPawn(newPawn, std::pair<int, int>(0, 0));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 1));
	AddPawn(newPawn, std::pair<int, int>(0, 4));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Brawler, 0));
	AddPawn(newPawn, std::pair<int, int>(1, 0));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Brawler, 1));
	AddPawn(newPawn, std::pair<int, int>(1, 4));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Sentinel, 0));
	AddPawn(newPawn, std::pair<int, int>(2, 0));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Sentinel, 1));
	AddPawn(newPawn, std::pair<int, int>(2, 4));
}

std::unique_ptr<GameState> GameState::Clone() const
{
	std::unique_ptr<GameState> copy = std::unique_ptr<GameState>(new GameState());
	copy->turnCounter = turnCounter;
	copy->currentPlayer = currentPlayer;
	copy->board.reserve(board.size());
	for (int row = 0; row < board.size(); ++row)
	{
		copy->board.push_back(std::vector<std::shared_ptr<Field>>());
		copy->board[row].reserve(board[row].size());
		for (int column = 0; column < board[row].size(); ++column)
		{
			copy->board[row].push_back(board[row][column]->Clone());
		}
	}
	for (auto& unit : pawnsOnBoard)
	{
		Pawn* newPawn = unit->Clone().release();
		newPawn->SetBoardCoordinates(newPawn->GetBoardCoordinates());
		copy->pawnsOnBoard.push_back(std::shared_ptr<Pawn>(newPawn));
	}
	return copy;
}

bool GameState::Equals(const GameState& other) const
{
	const GameState* temp = dynamic_cast<const GameState*>(&other);
	if (temp != nullptr)
	{
		if (currentPlayer != temp->currentPlayer || turnCounter != temp->turnCounter || board.size() != temp->board.size())
		{
			return false;
		}
		for (int row = 0; row < board.size(); ++row)
		{
			if (board[row].size() != temp->board[row].size())
			{
				for (int column = 0; column < board[row].size(); ++column)
				{
					if (!board[row][column]->Equals(*temp->board[row][column]))
					{
						return false;
					}
				}
			}
		}
		std::list<std::shared_ptr<Pawn>> ourPawns;
		for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
		{
			ourPawns.push_back(*iterator);
		}
		std::list<std::shared_ptr<Pawn>> theirPawns;
		for (auto iterator = temp->pawnsOnBoard.begin(); iterator != temp->pawnsOnBoard.end(); ++iterator)
		{
			theirPawns.push_back(*iterator);
		}
		bool foundMatch = false;
		while (ourPawns.size() > 0)
		{
			for (auto iterator = theirPawns.begin(); iterator != theirPawns.end(); ++iterator)
			{
				if (ourPawns.front()->Equals(**iterator))
				{
					ourPawns.pop_front();
					theirPawns.erase(iterator);
					foundMatch = true;
					break;
				}
			}
			if (!foundMatch)
			{
				return false;
			}
			foundMatch = false;
		}
		return true;
	}
	return false;
}

int GameState::PlayersCount() const
{
	return 2;
}

std::valarray<double> GameState::GetResult() const
{
	std::vector<double> playersPower{ 0.0,0.0 };
	for (auto& pawn : pawnsOnBoard)
	{
		playersPower[pawn->GetOwner()] += 1.0;
	}

	if (playersPower[0] == 0.0 && playersPower[1] > 0.0)
	{
		return { 0.0, 1.1 };
	}

	if (playersPower[1] == 0.0 && playersPower[0] > 0.0)
	{
		return { 1.1, 0.0 };
	}

	if (playersPower[0] == 0.0 && playersPower[1] == 0.0)
	{
		return { 0.5, 0.5 };
	}

	return { playersPower[0] / (playersPower[0] + playersPower[1]),  playersPower[1] / (playersPower[0] + playersPower[1]) };
}

int GameState::WhoPlay() const
{
	return currentPlayer;
}

std::vector<std::unique_ptr<const DefaultMove>> GameState::GetAllMoves() const
{
	std::vector<std::unique_ptr<const DefaultMove>> result = std::vector<std::unique_ptr<const DefaultMove>>();
	if(WhoPlay() != END_GAME)
	{
		result.push_back(std::make_unique<EndTurn>());
		for (auto& pawn : pawnsOnBoard)
		{
			if (pawn->GetOwner() == WhoPlay())
			{
				std::vector<UnitOrder*> newOrders = pawn->GetAvailableOrders(*this);
				for (auto order : newOrders)
				{
					result.push_back(std::unique_ptr<const DefaultMove>(order));
				}
			}
		}
	}
	return result;
}

bool GameState::PerformMove(const DefaultMove& move)
{
	if (move.IsValid(*this))
	{
		move.ApplyMove(*this);
		return true;
	}
	return false;
}

std::pair<int, int> GameState::GetBoardDimensions() const
{
	std::pair<int, int> result;
	if (board.size() > 0)
	{
		result.first = board.size();
		if (board[0].size() > 0)
		{
			result.second = board[0].size();
		}
		else
		{
			result.second = 0;
		}
	}
	else
	{
		result.first = 0;
		result.second = 0;
	}
	return result;
}


bool GameState::AddPawn(std::shared_ptr<Pawn> pawn, std::pair<int, int> coordinates)
{
	for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
	{
		if (iterator->get() == pawn.get())
		{
			assert(false && "Tried to add duplicate pawn");
			return false;
		}
	}
	if (coordinates.first < 0 || coordinates.first >= board.size() || coordinates.second < 0 || coordinates.second >= board[0].size())
	{
		assert(false && "Invalid coordinates");
		return false;
	}
	if (board[coordinates.first][coordinates.second]->slotsTaken < board[coordinates.first][coordinates.second]->GetCapacity())
	{
		pawnsOnBoard.push_back(pawn);
		++board[coordinates.first][coordinates.second]->slotsTaken;
		pawn->SetBoardCoordinates(coordinates);
		return true;
	}
	assert(false && "Slot is full");
	return false;
}

void GameState::RemovePawn(std::shared_ptr<Pawn> pawn)
{
	--board[pawn->GetBoardCoordinates().first][pawn->GetBoardCoordinates().second]->slotsTaken;
	pawnsOnBoard.remove(pawn);
}

std::vector<std::shared_ptr<Pawn>> GameState::GetPawnsOnCoordinates(std::pair<int, int> coordinates)
{
	std::vector<std::shared_ptr<Pawn>> result;
	if (coordinates.first < 0 || coordinates.first >= board.size() || coordinates.second < 0 || coordinates.second >= board[0].size())
	{
		assert(false && "Invalid coordinates");
		return result;
	}
	for(const auto& pawn : pawnsOnBoard)
	{
		if (pawn->GetBoardCoordinates() == coordinates)
		{
			result.push_back(pawn);
		}
	}
	return result;
}


//private
void GameState::TurnEnd()
{
	++currentPlayer;
	if (currentPlayer >= PlayersCount())
	{
		++turnCounter;
		BoardCycle();
		currentPlayer = IsWon() ? END_GAME : 0;
	}
}

void GameState::BoardCycle()
{
	std::list<std::shared_ptr<Pawn>> pawnsToRemove;
	for(auto& pawn : pawnsOnBoard)
	{
		if (pawn->GetHealth() > 0)
		{
			pawn->PerformAction(*this);
		}
	}
	for (auto& pawn : pawnsOnBoard)
	{
		if (pawn->GetHealth() <= 0)
		{
			pawnsToRemove.push_back(pawn);
		}
	}
	while(pawnsToRemove.size() > 0)
	{
		RemovePawn(pawnsToRemove.front());
		pawnsToRemove.pop_front();
	}
}

bool GameState::IsWon()
{
	if (currentPlayer == END_GAME)
	{
		return true;
	}

	if (turnCounter >= TURN_LIMIT)
	{
		currentPlayer = END_GAME;
		return true;
	}

	std::valarray<double> result = GetResult();
	for (int i = 0; i < result.size(); ++i)
	{
		if (result[i] > 1.0)
		{
			currentPlayer = END_GAME;
			return true;
		}
	}
	return false;
}