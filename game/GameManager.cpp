#include "GameManager.h"
#include "GameEvents.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

int GameManager::getCurrentPlayerIndex() const
{
	return currentPlayerIndex;
}

int GameManager::getHumanPlayerIndex() const
{
	return humanPlayerIndex;
}

bool GameManager::isCurrentPlayerHuman() const
{
	return getCurrentPlayerIndex() == getHumanPlayerIndex();
}

void GameManager::setupGame(int humanPlayer)
{
	humanPlayerIndex = humanPlayer;
	currentPlayerIndex = 0;
}

void GameManager::endTurn()
{
	currentPlayerIndex++;
	currentPlayerIndex %= playerCount;
	GameEvents::getInstance().onTurnFinished.broadcast();
}
