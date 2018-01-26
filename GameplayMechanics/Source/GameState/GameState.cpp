#include "GameState.h"
#include "..\Moves\DefaultMove.h"


//public
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

void GameState::applyMove(const grailMCTS::Move& move)
{

}

void GameState::applyMove(const DefaultMove& move)
{

}


//private