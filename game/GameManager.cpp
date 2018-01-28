#include "GameManager.h"
#include "GameEvents.h"
#include "GameplayManager.h"
#include "GameState/GameState.h"
#include "GameState/Pawn.h"
#include "Moves/EndTurn.h"
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
	auto& state = manager.GetCurrentGameState();
	auto dim = state.GetBoardDimensions();
	const auto& board = state.board;
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
		fieldComp->setSlotCount(board[row][col]->GetCapacity());
		fieldComp->setCoordinates({ row, col });
		sf::Vector2f pos = origin;
		float mult = cols / 2.0f - col - 0.5f;
		pos.x -= mult * fieldSeparation;
		pos.y += row * fieldSeparation;
		field.setPosition(pos);

		auto pawns = state.GetPawnsOnCoordinates({ row, col });
		for (auto& pawn : pawns)
		{
			auto iter = pawnPrefabs.find(pawn->GetUnitType());
			if (iter != pawnPrefabs.end())
			{
				auto& pawnObj = iter->second.instantiate(scene);
				auto pawnComp = pawnObj.getComponent<Pawn>();
				pawnComp->setOwnerIndex(pawn->GetOwner());
				pawnComp->setCurrentField(fieldComp.get());
				pawnComp->setGameStatePawn(pawn.get());
				if (pawnComp->getOwnerIndex() == 0)
				{
					pawnComp->setColors(sf::Color::Green, sf::Color::Blue);
				}
				else
				{
					pawnComp->setColors(sf::Color::Red, sf::Color::Red);
				}
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
	Game::GameplayManager::GetInstance().GetCurrentGameState().PerformMove(Game::EndTurn());
	Game::GameplayManager::GetInstance().AI_PerformTurn();
}
