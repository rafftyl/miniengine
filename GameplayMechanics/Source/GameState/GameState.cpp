#include "GameState.h"
#include "Field.h"
#include "..\Moves\DefaultMove.h"
#include "..\Moves\EndTurn.h"
using namespace Game;


//public
GameState::GameState()
{
	currentPlayer = 0;
	board = std::vector<std::vector<std::shared_ptr<Field>>>();
	//TODO: przeniesienie konstrukcji planszy
	board.resize(4);
	for (int row = 0; row < board.size(); ++row)
	{
		board[row].resize(5);
		for (int column = 0; column < board[row].size(); ++column)
		{
			board[row][column] = std::shared_ptr<Field>(new Field(4));
		}
	}
}

std::unique_ptr<GameState> GameState::clone() const
{
	std::unique_ptr<GameState> copy = std::unique_ptr<GameState>(new GameState());
	copy->currentPlayer = currentPlayer;
	copy->board.resize(board.size());
	for (int row = 0; row < board.size(); ++row)
	{
		copy->board[row].resize(board[row].size());
		for (int column = 0; column < board[row].size(); ++column)
		{
			copy->board[row][column] = std::move(board[row][column]->clone());
		}
	}
	return copy;
}

bool GameState::equals(const GameState& other) const
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
					if (!board[row][column]->equals(*temp->board[row][column]))
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
	result.first = board.size();
	result.second = board[0].size();
	return result;
}

std::shared_ptr<const Field> GameState::GetField(int row, int column) const
{
	return board[row][column];
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
	//TODO: cykl planszy
}

bool GameState::IsWon()
{
	//TODO: sprawdzanie wygranej
	return false;
}