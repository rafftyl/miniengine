#include "GameplayManager.h"
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
	Initialize();
}

bool GameplayManager::AI_PerformTurn()
{
	int currentPlayer = currentGameState->whoPlay();
	if (currentPlayer != grailMCTS::TERMINAL)
	{
		while (currentPlayer == currentGameState->whoPlay())
		{
			mcts.setRoot(currentGameState->clone());
			mcts.runIterationsTotal(ITERATIONS);
			currentGameState->applyMove({ *mcts.highestResultMove() });
		}
	}
	return false;
}


//private
void GameplayManager::Initialize()
{
	currentGameState = std::make_unique<GameState>();
	mcts.setRoot(currentGameState->clone());
}

GameplayManager::GameplayManager()
{
	Initialize();
}

GameplayManager::~GameplayManager()
{

}