#include "GameManager.h"
#include "GameEvents.h"
#include "Field.h"

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

void GameManager::setupGame(int humanPlayer, mini::Scene& scene, mini::Prefab& pawnPrefab, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation)
{
	int cols = 5;
	int rows = 4;
	humanPlayerIndex = humanPlayer;
	currentPlayerIndex = 0;
	for (int index = 0; index < cols * rows; ++index)
	{
		int row = index / cols;
		int col = index - row * cols;
		auto& field = fieldPrefab.instantiate(scene);
		field.getComponent<Field>()->setSlotCount(4);
		field.getComponent<Field>()->setCoordinates({ row, col });
		sf::Vector2f pos = origin;
		float mult = cols / 2.0f - col - 0.5f;
		pos.x -= mult * fieldSeparation;
		pos.y += row * fieldSeparation;
		field.setPosition(pos);
	}
}

void GameManager::endTurn()
{
	currentPlayerIndex++;
	currentPlayerIndex %= playerCount;
	GameEvents::getInstance().onTurnFinished.broadcast();
}
