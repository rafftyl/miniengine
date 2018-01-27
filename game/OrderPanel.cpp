#include "OrderPanel.h"
#include "GameEvents.h"
#include "GameplaySystem.h"
#include "GameObject.h"
#include "Pawn.h"
#include "UIButton.h"

OrderPanel::OrderPanel(mini::GameObject& owner) : mini::Component(owner)
{
}

OrderPanel::~OrderPanel()
{
}

void OrderPanel::start()
{
	GameEvents::getInstance().onPawnSelected.addCallback([&](Pawn& pawn) {initForPawn(pawn); });
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
	owner.setActive(true);
	for (int i = 0; i < buttonLayoutDimensions.x * buttonLayoutDimensions.y; ++i) //iterate over actions
	{
		int row = i / buttonLayoutDimensions.x;
		int col = i - row * buttonLayoutDimensions.x;
		auto& buttonObj = upArrowPrefab.instantiate(getGameplaySystem());
		sf::Vector2f localPos = buttonLayoutOrigin;
		localPos.x -= (buttonLayoutDimensions.x / 2.0f - col - 0.5f) * buttonSeparation;
		localPos.y += row * buttonSeparation;
		buttonObj.setPosition(owner.getPosition() + buttonLayoutOrigin - localPos);
		spawnedButtons.push_back(&buttonObj);
		buttonObj.getComponent<UIButton>()->onClicked().addCallback([&](UIButton& button) {}); //launch ability
	}
}
