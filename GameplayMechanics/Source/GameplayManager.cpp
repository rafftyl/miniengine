#include "GameplayManager.h"
#include "GameState\GameState.h"
#include "Moves\DefaultMove.h"
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
	int currentPlayer = currentGameState->whoPlay();
	if (movesToAnimate.size() == 0 && currentPlayer != grailMCTS::TERMINAL)
	{
		while (currentPlayer == currentGameState->whoPlay())
		{
			mcts.setRoot(currentGameState->clone());
			mcts.runIterationsTotal(ITERATIONS);
			std::unique_ptr<grailMCTS::Move> move = mcts.highestResultMove();
			currentGameState->applyMove({ *move });
			movesToAnimate.push_back(std::unique_ptr<DefaultMove>(static_cast<DefaultMove*>(move.release())));
		}
		return true;
	}
	return false;
}

std::list<std::unique_ptr<DefaultMove>> GameplayManager::GetMovesToAnimate()
{
	std::list<std::unique_ptr<DefaultMove>> result = std::list<std::unique_ptr<DefaultMove>>();
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
	mcts.setRoot(currentGameState->clone());
}

GameplayManager::GameplayManager()
{
	mcts = grailMCTS::MCTS();
	movesToAnimate = std::list<std::unique_ptr<DefaultMove>>();
	Initialize();
}

GameplayManager::~GameplayManager()
{

}