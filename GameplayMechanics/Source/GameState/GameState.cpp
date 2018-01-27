#include "GameState.h"
#include "Field.h"
#include "Pawn.h"
#include "..\Moves\DefaultMove.h"
#include "..\Moves\EndTurn.h"
#include <iostream>
using namespace Game;

//public
void GameState::Initialize()
{
	//TODO: przeniesienie konstrukcji planszy
	currentPlayer = 0;
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
	AddPawn(newPawn, 0, 0);
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 0));
	AddPawn(newPawn, 0, 0);
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 1));
	AddPawn(newPawn, 0, 4);
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 1));
	AddPawn(newPawn, 3, 4);
}

std::unique_ptr<GameState> GameState::Clone() const
{
	std::unique_ptr<GameState> copy = std::make_unique<GameState>();
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
	for (auto& unit : unitsOnBoard)
	{
		Pawn* newPawn = unit->Clone().release();
		newPawn->SetField(newPawn->GetBoardCoordinates(), *copy);
		copy->unitsOnBoard.push_back(std::shared_ptr<Pawn>(newPawn));
	}
	return copy;
}

bool GameState::Equals(const GameState& other) const
{
	const GameState* temp = dynamic_cast<const GameState*>(&other);
	if (temp != nullptr)
	{
		if (currentPlayer != temp->currentPlayer)
		{
			return false;
		}
		if (board.size() != temp->board.size())
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
		return true;
	}
	return false;
}

int GameState::PlayersCount() const
{
	return 2;
}

std::vector<double> GameState::GetResult() const
{
	std::vector<double> result;
	result.resize(PlayersCount());
	//TODO: określanie wyniku w stanie terminalnym
	return result;
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

std::shared_ptr<const Field> GameState::GetField(int row, int column) const
{
	return board.at(row).at(column);
}

std::shared_ptr<Field> GameState::GetField(int row, int column)
{
	return board[row][column];
}

bool GameState::AddPawn(std::shared_ptr<Pawn> pawn, int row, int column)
{
	if (pawn->SetField(std::pair<int, int>(row, column), *this))
	{
		unitsOnBoard.push_back(pawn);
		board[row][column]->InsertPawn(pawn);
		return true;
	}
	return false;
}

void GameState::RemovePawn(std::shared_ptr<Pawn>)
{

}


//private
void GameState::TurnEnd()
{
	++currentPlayer;
	if (currentPlayer >= PlayersCount())
	{
		BoardCycle();
		currentPlayer = IsWon() ? END_GAME : 0;
	}
}

void GameState::BoardCycle()
{
	for (auto iterator = unitsOnBoard.begin(); iterator == unitsOnBoard.end(); ++iterator)
	{
		iterator->get()->PerformAction(*this);
	}
}

bool GameState::IsWon()
{
	//TODO: sprawdzanie wygranej
	return false;
}