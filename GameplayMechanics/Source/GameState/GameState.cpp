#include "GameState.h"
#include "..\Moves\DefaultMove.h"
#include "Field.h"
using namespace Game;


//public
GameState::GameState()
{
	board = std::vector<std::vector<std::unique_ptr<Field>>>();
}

std::unique_ptr<grailMCTS::GameState> GameState::clone() const
{
	std::unique_ptr<grailMCTS::GameState> copy = std::unique_ptr<grailMCTS::GameState>();
	return copy;
}

bool GameState::equals(const grailMCTS::GameState& other) const
{
	const GameState* temp = dynamic_cast<const GameState*>(&other);
	if (temp != nullptr)
	{
		//TODO: sprawdzenie informacji globalnych
		if (board.size() != temp->board.size())
		{
			return false;
		}
		for (int rows = 0; rows < board.size(); ++rows)
		{
			if (board[rows].size() != temp->board[rows].size())
			{
				for (int columns = 0; columns < board[rows].size(); ++columns)
				{
					if (!board[rows][columns]->equals(*temp->board[rows][columns]))
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
	return 0;
}

grailMCTS::Result GameState::getResult() const
{
	std::valarray<double> result;
	result.resize(playersCount());
	return result;
}

int GameState::whoPlay() const
{
	return grailMCTS::TERMINAL;
}

std::vector<std::unique_ptr<const grailMCTS::Move>> GameState::getMoves() const
{
	std::vector<std::unique_ptr<const grailMCTS::Move>> result = std::vector<std::unique_ptr<const grailMCTS::Move>>();
	return result;
}

//Rafał nie ruszaj plz (to je dla MCTS), używaj "PerformMove(const DefaultMove& move)"
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