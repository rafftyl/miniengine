#include "MctsGameState.h"
#include "GameState.h"
#include "..\Moves\DefaultMove.h"
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
	return gameState->GetResult();
}

int MctsGameState::whoPlay() const
{
	if (!gameState->IsWon())
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
	std::vector<std::unique_ptr<const grailMCTS::Move>> result;
	auto myMoves = gameState->GetAllMoves();
	for (auto& move : myMoves)
	{
		result.push_back(std::make_unique<MctsMove>(move.release()));
	}
	return result;
}

void MctsGameState::applyMove(const grailMCTS::Move& move)
{
	gameState->PerformMove(*static_cast<Game::MctsMove&>(*move.clone()).GetMove());
}