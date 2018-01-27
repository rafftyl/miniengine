#include "GameManager.h"
#include "GameEvents.h"
#include "GameplayManager.h"
#include "GameState/GameState.h"
#include "GameState/Field.h"
#include "Pawn.h"
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

void GameManager::setupGame(int humanPlayer, mini::Scene& scene, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation)
{
	Game::GameplayManager& manager = Game::GameplayManager::GetInstance();
	const auto& state = manager.GetCurrentGameState();
	auto dim = state.GetBoardDimensions();
	int rows = dim.first;
	int cols = dim.second;
	humanPlayerIndex = humanPlayer;
	currentPlayerIndex = 0;
	for (int index = 0; index < cols * rows; ++index)
	{
		int row = index / cols;
		int col = index - row * cols;
		auto& field = fieldPrefab.instantiate(scene);
		auto fieldComp = field.getComponent<Field>();
		fieldComp->setSlotCount(state.GetField(row, col)->GetCapacity());
		fieldComp->setCoordinates({ row, col });
		sf::Vector2f pos = origin;
		float mult = cols / 2.0f - col - 0.5f;
		pos.x -= mult * fieldSeparation;
		pos.y += row * fieldSeparation;
		field.setPosition(pos);

		auto pawns = state.GetField(row, col)->GetPawns();
		for (auto& pawn : pawns)
		{
			auto iter = pawnPrefabs.find(const_cast<Game::Pawn*>(pawn.get())->GetUnitType());
			if (iter != pawnPrefabs.end())
			{
				auto& pawnObj = iter->second.instantiate(scene);
				auto pawnComp = pawnObj.getComponent<Pawn>();
				pawnComp->setOwnerIndex(pawn->GetOwner());
				pawnComp->setGameStatePawn(pawn);
				pawnComp->setCurrentField(fieldComp.get());
				fieldComp->addPawn(pawnComp.get());				
			}
		}
	}
}

void GameManager::reloadSceneWithNewState(mini::GameplaySystem& gameplaySys, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation)
{
	mini::Scene& scene = gameplaySys.getCurrentScene();
	gameplaySys.loadScene(scene.getName());
}

void GameManager::endTurn()
{
	currentPlayerIndex++;
	currentPlayerIndex %= playerCount;
	GameEvents::getInstance().onTurnFinished.broadcast();
}
