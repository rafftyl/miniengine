#include "MctsGameState.h"
#include "GameState.h"
#include "..\Moves\MctsMove.h"
using namespace Game;


//public
MctsGameState::MctsGameState(Game::GameState* _gameState)
{
	gameState = std::unique_ptr<Game::GameState>(_gameState);
}

std::unique_ptr<grailMCTS::GameState> MctsGameState::clone() const
{
	return std::unique_ptr<MctsGameState>(new MctsGameState(gameState->Clone().release()));
}

bool MctsGameState::equals(const grailMCTS::GameState& other) const
{
	const MctsGameState* temp = dynamic_cast<const MctsGameState*>(&other);
	if (temp != nullptr)
	{
		return gameState->Equals(*temp->gameState);
	}
}

std::size_t MctsGameState::playersCount() const
{
	return gameState->PlayersCount();
}

grailMCTS::Result MctsGameState::getResult() const
{
	std::vector<double> myResult = gameState->GetResult();
	std::valarray<double> result;
	result.resize(myResult.size());
	int index = 0;
	while (myResult.size() > 0)
	{
		result[index] = myResult.back();
		myResult.pop_back();
	}
	return result;
}

int MctsGameState::whoPlay() const
{
	if (gameState->WhoPlay() >= 0)
	{
		return gameState->WhoPlay();
	}
	else
	{
		return grailMCTS::TERMINAL;
	}
}

std::vector<std::unique_ptr<const grailMCTS::Move>> MctsGameState::getMoves() const
{
	/*
	std::vector<std::unique_ptr<const DefaultMove>> myMoves = gameState->GetAllMoves();
	std::vector<std::unique_ptr<const grailMCTS::Move>> result;
	for (auto iterator = myMoves.begin(); iterator != myMoves.end(); ++iterator)
	{
		result.push_back(std::unique_ptr<const MctsMove>(new MctsMove(iterator->release())));
	}
	return result;
	*/
	std::vector<std::unique_ptr<const grailMCTS::Move>> result;
	return result;
}

void MctsGameState::applyMove(const grailMCTS::Move& move)
{

}