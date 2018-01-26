#include "GameplayManager.h"


//public
GameplayManager& GameplayManager::GetInstance()
{
	static GameplayManager instance;
	return instance;
}

void GameplayManager::RunGame()
{

}

GameState* GameplayManager::GetCurrentGameState()
{
	return currentGameState.get();
}


//private
GameplayManager::GameplayManager()
{

}

GameplayManager::~GameplayManager()
{

}