﻿#include "GameplayManager.h"
#include <MCTS.h>
#include "GameState\GameState.h"
#include "GameState\MctsGameState.h"
#include "Moves\DefaultMove.h"
#include "Moves\MctsMove.h"
#define ITERATIONS 250
using namespace Game;


//public
GameplayManager& GameplayManager::GetInstance()
{
	static GameplayManager instance;
	return instance;
}

GameState& GameplayManager::GetCurrentGameState() 
{
	return *currentGameState;
}

void GameplayManager::RestartGame()
{
	movesToAnimate.clear();
	currentGameState = std::make_unique<GameState>();
	currentGameState->Initialize();
	MctsGameState state(currentGameState->Clone().release());
	mcts->setRoot(state);
}

void GameplayManager::AI_PerformTurn()
{
	int currentPlayer = currentGameState->WhoPlay();
	if (currentPlayer >= 0)
	{
		while (currentPlayer == currentGameState->WhoPlay())
		{
			MctsGameState state(currentGameState->Clone().release());
			mcts->setRoot(state);
			mcts->runIterationsTotal(ITERATIONS);
			std::unique_ptr<const DefaultMove> move = static_cast<Game::MctsMove&>(*mcts->highestResultMove()).GetMove();
			currentGameState->PerformMove(*move);
			movesToAnimate.push_back(std::move(move));
		}
		if (onAnimationQueueCreated != nullptr)
		{
			onAnimationQueueCreated(movesToAnimate);
		}
		movesToAnimate.clear();
		if (onNewGameStateFound != nullptr)
		{
			onNewGameStateFound(*currentGameState);
		}
	}
}


//private
GameplayManager::GameplayManager()
{
	movesToAnimate = std::list<std::unique_ptr<const DefaultMove>>();
	currentGameState = std::make_unique<GameState>();
	currentGameState->Initialize();
	MctsGameState state(currentGameState->Clone().release());
	mcts = std::make_unique<grailMCTS::MCTS>(state, grailMCTS::Configuration().with(grailMCTS::Configuration::PERFECTONLY_OR_CHEATING_WITH_STATES_IN_NODES));
}

GameplayManager::~GameplayManager()
{

}