#include "GameManager.h"
#include "GameEvents.h"
#include "GameplayManager.h"
#include "GameState/GameState.h"
#include "GameState/Pawn.h"
#include "Moves/EndTurn.h"
#include "Pawn.h"
#include "Field.h"
#include <thread>

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

bool GameManager::isHumanPlayer(int index) const
{
	return humanPlayerIndices.find(index) != humanPlayerIndices.end();
}

bool GameManager::isCurrentPlayerHuman() const
{
	return humanPlayerIndices.find(getCurrentPlayerIndex()) != humanPlayerIndices.end();
}

void GameManager::setupGame(std::set<int> humanPlayers, mini::Scene& scene, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation)
{
	fields.clear();
	Game::GameplayManager& manager = Game::GameplayManager::GetInstance();
	auto& state = manager.GetCurrentGameState();
	auto dim = state.GetBoardDimensions();
	const auto& board = state.board;
	int rows = dim.first;
	int cols = dim.second;
	humanPlayerIndices = humanPlayers;
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
		fields.push_back(fieldComp);		
	}

	auto pawns = state.pawnsOnBoard;
	int initiative = 1;
	for (auto& pawn : pawns)
	{
		auto iter = pawnPrefabs.find(pawn->GetUnitType());
		if (iter != pawnPrefabs.end())
		{
			auto& pawnObj = iter->second.instantiate(scene);
			auto pawnComp = pawnObj.getComponent<Pawn>();
			pawnComp->setOwnerIndex(pawn->GetOwner());
			auto coords = pawn->GetBoardCoordinates();
			auto fieldIter = std::find_if(fields.begin(), fields.end(), [&](const auto& field) {return field->getCoordinates().x == coords.first && field->getCoordinates().y == coords.second;});
			if (fieldIter != fields.end())
			{
				auto fieldComp = *fieldIter;
				pawnComp->setCurrentField(fieldComp.get());
				pawnComp->setGameStatePawn(pawn);
				pawnComp->initiativeIndex = initiative;
				if (pawnComp->getOwnerIndex() == 0)
				{
					pawnComp->setColors(sf::Color::Green, sf::Color::Blue);
				}
				else
				{
					pawnComp->setColors(sf::Color::Green, sf::Color::Red);
				}
				fieldComp->addPawn(pawnComp.get());
			}
			++initiative;
		}
	}
}

void GameManager::reloadSceneWithNewState(mini::GameplaySystem& gameplaySys, std::map<Game::PawnType, mini::Prefab>& pawnPrefabs, mini::Prefab& fieldPrefab, const sf::Vector2f& origin, float fieldSeparation)
{
	GameEvents::getInstance().clearEvents();
	mini::Scene& scene = gameplaySys.getCurrentScene();
	gameplaySys.loadScene(scene.getName());
}

void GameManager::endTurn(bool requestAIMove)
{
	currentPlayerIndex++;
	currentPlayerIndex %= playerCount;
	if (currentPlayerIndex == 0)
	{
		GameEvents::getInstance().onGameStateChanged.broadcast(Game::GameplayManager::GetInstance().GetCurrentGameState());
	}
	GameEvents::getInstance().onTurnFinished.broadcast();
	if (requestAIMove && !isCurrentPlayerHuman())
	{
		if (aiOrderThread != nullptr)
		{
			aiOrderThread->join();
		}
		if (aiBusyText)
		{
			aiBusyText->setActive(true);
		}
		aiOrderThread = std::make_unique<std::thread>([&] {
			Game::GameplayManager::GetInstance().AI_PerformTurn(); 
			if (aiBusyText)
			{
				aiBusyText->setActive(false);
			}
		});
	}		
}
