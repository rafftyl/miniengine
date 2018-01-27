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

void GameManager::setupGame(int humanPlayer, mini::Scene& scene, mini::Prefab& fieldPrefab, std::vector<size_t> fieldCapacities, int cols, const sf::Vector2f& origin, float fieldSeparation)
{
	humanPlayerIndex = humanPlayer;
	currentPlayerIndex = 0;
	int index = 0;
	for (size_t capacity : fieldCapacities)
	{
		int row = index / cols;
		int col = index - row * cols;
		auto& field = fieldPrefab.instantiate(scene);
		field.getComponent<Field>()->setSlotCount(capacity);
		sf::Vector2f pos = origin;
		int mult = cols / 2 - col;
		pos.x -= mult * fieldSeparation;
		pos.y += row * fieldSeparation;
		field.setPosition(pos);
		index++;
	}
}

void GameManager::endTurn()
{
	currentPlayerIndex++;
	currentPlayerIndex %= playerCount;
	GameEvents::getInstance().onTurnFinished.broadcast();
}
