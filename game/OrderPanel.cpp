#include "OrderPanel.h"
#include "GameEvents.h"
#include "GameplaySystem.h"
#include "GameObject.h"
#include "Pawn.h"
#include "UIButton.h"
#include "Moves/DefaultMove.h"
#include "GameManager.h"
#include "GameplayManager.h"
#include "GameState/Pawn.h"
#include "Moves/EndTurn.h"
#include "Moves/UnitOrder.h"
#include <array>

OrderPanel::OrderPanel(mini::GameObject& owner) : mini::Component(owner)
{
}

OrderPanel::~OrderPanel()
{
}

void OrderPanel::start()
{
	GameEvents::getInstance().onPawnSelected.addCallback(
		[&](Pawn& pawn)
	{
		for (auto buttonObj : spawnedButtons)
		{
			gameplaySystem->destroyObject(*buttonObj);
		}
		initForPawn(pawn); 
	});
	GameEvents::getInstance().onPawnUnselected.addCallback([&]()
	{
		for (auto buttonObj : spawnedButtons)
		{
			gameplaySystem->destroyObject(*buttonObj);
		}
		spawnedButtons.clear();
		owner.setActive(false);
	});	

	owner.setActive(false);
}

void OrderPanel::setParams(const sf::Vector2f& origin, const sf::Vector2i& layoutSize, float separation, mini::Prefab upPrefab)
{
	buttonLayoutOrigin = origin;
	buttonLayoutDimensions = layoutSize;
	buttonSeparation = separation;
	upArrowPrefab = upPrefab;
}

void OrderPanel::initForPawn(const Pawn& pawn)
{
	filteredMoves.clear();
	auto moves = Game::GameplayManager::GetInstance().GetCurrentGameState().GetAllMoves();
	for (auto& move : moves)
	{
		auto endTurn = dynamic_cast<const Game::EndTurn*>(move.get());
		if (endTurn == nullptr)
		{
			auto order = dynamic_cast<const Game::UnitOrder*>(move.get());
			if (order != nullptr && order->targetPawn == pawn.getGameStatePawn().lock().get())
			{
				filteredMoves.push_back(std::move(move));
			}
		}
	}
	owner.setActive(true);
	
	int i = 0;
	for (auto& move : filteredMoves) //iterate over actions
	{
		int row = i / buttonLayoutDimensions.x;
		int col = i - row * buttonLayoutDimensions.x;
		auto& buttonObj = upArrowPrefab.instantiate(getGameplaySystem());
		sf::Vector2f localPos = buttonLayoutOrigin;
		localPos.x -= (buttonLayoutDimensions.x / 2.0f - col - 0.5f) * buttonSeparation;
		localPos.y += row * buttonSeparation;
		sf::Vector2f pos = owner.getPosition() + localPos;
		buttonObj.setPosition(pos);
		spawnedButtons.push_back(&buttonObj);
		std::array<float, 4> angles{ 0, 90, 180, 270 };
		auto order = dynamic_cast<const Game::UnitOrder*>(move.get());
		switch (order->orderType)
		{
		case Game::OrderType::Advance:
			buttonObj.setRotation(angles[static_cast<int>(order->direction)]);
			break;
		case Game::OrderType::Stop:
			buttonObj.setRotation(38);
			break;
		default:
			break;
		}

		buttonObj.getComponent<UIButton>()->onMouseEnter().addCallback([&](UIButton& button)
		{
			button.getOwner().getComponent<mini::Renderer>()->setColor(sf::Color::Green);
		});

		buttonObj.getComponent<UIButton>()->onMouseExit().addCallback([&](UIButton& button)
		{
			button.getOwner().getComponent<mini::Renderer>()->setColor(sf::Color::White);
		}); 

		buttonObj.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) 
		{
			auto& state = Game::GameplayManager::GetInstance().GetCurrentGameState();
			state.PerformMove(*move);
			Pawn::selectedPawn->setHighlighted(false);
			GameManager::getInstance().endTurn();
		}); //launch ability
		++i;
	}
}
