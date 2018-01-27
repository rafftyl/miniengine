#include "GameplayManager.h"
#include <MCTS.h>
#include "GameState\GameState.h"
#include "GameState\MctsGameState.h"
#include "Moves\DefaultMove.h"
#include "Moves\MctsMove.h"
#define ITERATIONS 100
using namespace Game;


//public
GameplayManager& GameplayManager::GetInstance()
{
	static GameplayManager instance;
	return instance;
}

const GameState& GameplayManager::GetCurrentGameState() const
{
	return *currentGameState;
}

void GameplayManager::RestartGame()
{
	movesToAnimate.clear();
	Initialize();
}

bool GameplayManager::AI_PerformTurn()
{
	int currentPlayer = currentGameState->WhoPlay();
	if (movesToAnimate.size() == 0 && currentPlayer >= 0)
	{
		while (currentPlayer == currentGameState->WhoPlay())
		{
			mcts->setRoot(*new MctsGameState(currentGameState->Clone().release()));
			mcts->runIterationsTotal(ITERATIONS);
			std::unique_ptr<const DefaultMove> move = static_cast<Game::MctsMove&>(*mcts->highestResultMove()).GetMove();
			currentGameState->PerformMove(*move);
			movesToAnimate.push_back(std::move(move));
		}
		return true;
	}
	return false;
}

std::list<std::unique_ptr<const DefaultMove>> GameplayManager::GetMovesToAnimate()
{
	std::list<std::unique_ptr<const DefaultMove>> result = std::list<std::unique_ptr<const DefaultMove>>();
	while (movesToAnimate.size() > 0)
	{
		result.push_back(std::move(movesToAnimate.front()));
		movesToAnimate.pop_front();
	}
	return result;
}


//private
void GameplayManager::Initialize()
{
	currentGameState = std::make_unique<GameState>();
	mcts->setRoot(*new MctsGameState(currentGameState->Clone().release()));
}

GameplayManager::GameplayManager()
{
	mcts = std::unique_ptr<grailMCTS::MCTS>(new grailMCTS::MCTS());
	movesToAnimate = std::list<std::unique_ptr<const DefaultMove>>();
	Initialize();
}

GameplayManager::~GameplayManager()
{

}