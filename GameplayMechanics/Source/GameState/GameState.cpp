#include "GameState.h"
#include "Field.h"
#include "..\Moves\DefaultMove.h"
#include "..\Moves\EndTurn.h"
using namespace Game;


//public
GameState::GameState()
{
	currentPlayer = 0;
	board = std::vector<std::vector<std::unique_ptr<Field>>>();
}

std::unique_ptr<grailMCTS::GameState> GameState::clone() const
{
	std::unique_ptr<GameState> copy = std::unique_ptr<GameState>();
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

bool GameState::equals(const grailMCTS::GameState& other) const
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

std::size_t GameState::playersCount() const
{
	return 2;
}

grailMCTS::Result GameState::getResult() const
{
	std::valarray<double> result;
	result.resize(playersCount());
	//TODO: określanie wyniku w stanie terminalnym
	return result;
}

int GameState::whoPlay() const
{
	return currentPlayer;
}

std::vector<std::unique_ptr<const grailMCTS::Move>> GameState::getMoves() const
{
	std::vector<std::unique_ptr<const grailMCTS::Move>> result = std::vector<std::unique_ptr<const grailMCTS::Move>>();
	if (whoPlay() != grailMCTS::TERMINAL)
	{
		result.push_back(std::make_unique<EndTurn>());
	}
	return result;
}

//Rafał nie ruszaj plz (to je dla MCTS), używaj "PerformMove()"
void GameState::applyMove(const grailMCTS::Move& move)
{
	PerformMove(static_cast<const DefaultMove&>(move));
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


//private
void GameState::TurnEnd()
{
	++currentPlayer;
	if (currentPlayer >= playersCount())
	{
		BoardCycle();
		currentPlayer = IsWon() ? grailMCTS::TERMINAL : 0;
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