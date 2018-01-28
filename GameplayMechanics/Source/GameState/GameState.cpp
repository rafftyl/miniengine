#include "GameState.h"
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
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 0));
	AddPawn(newPawn, std::pair<int, int>(0, 0));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 1));
	AddPawn(newPawn, std::pair<int, int>(0, 4));
	newPawn = std::shared_ptr<Pawn>(new Pawn(PawnType::Thug, 1));
	AddPawn(newPawn, std::pair<int, int>(3, 4));
}

std::unique_ptr<GameState> GameState::Clone() const
{
	std::unique_ptr<GameState> copy = std::unique_ptr<GameState>(new GameState());
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
	std::vector<double> playersPower(0.0, 0.0);
	for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
	{
		playersPower[iterator->get()->GetOwner()] += 1.0;
	}
	if (playersPower[0] == 0.0 && playersPower[1] > 0.0)
	{
		result[0] = 0.0;
		result[1] = 1.1;
		return result;
	}
	if (playersPower[1] == 0.0 && playersPower[0] > 0.0)
	{
		result[0] = 1.1;
		result[1] = 0.0;
		return result;
	}
	if (playersPower[0] == 0.0 && playersPower[1] == 0.0)
	{
		result[0] = 0.5;
		result[1] = 0.5;
		return result;
	}
	result[0] = playersPower[0] / playersPower[1];
	result[1] = playersPower[1] / playersPower[0];
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
		for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
		{
			if (iterator->get()->GetOwner() == WhoPlay())
			{
				std::vector<UnitOrder*> newOrders = iterator->get()->GetAvailableOrders(*this);
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
			return false;
		}
	}
	if (coordinates.first < 0 || coordinates.first >= board.size() || coordinates.second < 0 || coordinates.second >= board[0].size())
	{
		return false;
	}
	if (board[coordinates.first][coordinates.second]->slotsTaken < board[coordinates.first][coordinates.second]->GetCapacity())
	{
		pawnsOnBoard.push_back(pawn);
		++board[coordinates.first][coordinates.second]->slotsTaken;
		pawn->SetBoardCoordinates(coordinates);
		return true;
	}
	return false;
}

void GameState::RemovePawn(std::shared_ptr<Pawn> pawn)
{
	for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
	{
		if (iterator->get() == pawn.get())
		{
			--board[iterator->get()->GetBoardCoordinates().first][iterator->get()->GetBoardCoordinates().second]->slotsTaken;
			pawnsOnBoard.erase(iterator);
			break;
		}
	}
}

std::vector<std::shared_ptr<Pawn>> GameState::GetPawnsOnCoordinates(std::pair<int, int> coordinates)
{
	std::vector<std::shared_ptr<Pawn>> result;
	for (auto iterator = pawnsOnBoard.begin(); iterator != pawnsOnBoard.end(); ++iterator)
	{
		if (iterator->get()->GetBoardCoordinates() == coordinates)
		{
			result.push_back(*iterator);
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
	for (auto iterator = pawnsOnBoard.begin(); iterator == pawnsOnBoard.end(); ++iterator)
	{
		iterator->get()->PerformAction(*this);
	}
}

bool GameState::IsWon()
{
	if (turnCounter >= TURN_LIMIT)
	{
		return true;
	}
	std::vector<double> result = GetResult();
	for (auto iterator = result.begin(); iterator != result.end(); ++iterator)
	{
		if (*iterator >= 1.0)
		{
			return true;
		}
	}
	return false;
}