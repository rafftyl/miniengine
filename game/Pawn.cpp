#include "Pawn.h"
#include "GameEvents.h"
#include "GameObject.h"
#include "GameManager.h"
#include "GameState/Pawn.h"

Pawn* Pawn::selectedPawn = nullptr;

Pawn::Pawn(mini::GameObject& owner) : Targetable(owner)
{
}

Pawn::~Pawn()
{
}

void Pawn::start()
{
	Targetable::start();
	pawnSelectedCallbackHandle = GameEvents::getInstance().onPawnSelected.addCallback(
		[&](Pawn& pawn) 
	{
		if (isSelected && this != &pawn) 
		{ 
			isSelected = false;
			renderer->setColor(normalColor);
		}
	});

	stateChangedCallbackHandle = GameEvents::getInstance().onGameStateChanged.addCallback(
		[&](Game::GameState& state)
	{
		if (gameStatePawn.expired())
		{
			markedForDestroy = true;
		}
		else
		{
			const auto& fields = GameManager::getInstance().fields;
			for (auto& field : fields)
			{
				auto pawns = state.GetPawnsOnCoordinates({ field->getCoordinates().x, field->getCoordinates().y });
				auto pawnIter = std::find_if(pawns.begin(), pawns.end(), [&](const auto& pwn)->bool {return pwn == gameStatePawn.lock(); });
				if (pawnIter != pawns.end())
				{
					field->movePawnToField(this);
				}
			}
		}
	});

	initiativeLabel = &labelPrefab.instantiate(getGameplaySystem());
	initiativeLabel->setScreenSpace(false);
	auto textRenderer = initiativeLabel->getComponent<mini::TextRenderer>();
	textRenderer->setColor(sf::Color::White);
	textRenderer->setCharacterSize(20);
	textRenderer->setLayer(4);
	std::stringstream ss;
	ss << initiativeIndex;
	textRenderer->setText(ss.str());
}

void Pawn::update()
{
	if (markedForDestroy)
	{
		getGameplaySystem().destroyObject(*initiativeLabel);
		getGameplaySystem().destroyObject(owner);
	}
	else
	{
		initiativeLabel->setPosition(owner.getPosition() + sf::Vector2f(20, 20));
	}
}

void Pawn::destroy()
{
	Targetable::destroy();
	GameEvents::getInstance().onPawnSelected.removeCallback(pawnSelectedCallbackHandle);
	GameEvents::getInstance().onGameStateChanged.removeCallback(stateChangedCallbackHandle);
	if (currentField != nullptr)
	{
		currentField->removePawn(this);
	}
}

void Pawn::setOwnerIndex(int index)
{
	ownerIndex = index;
}

int Pawn::getOwnerIndex() const
{
	return ownerIndex;
}

void Pawn::setHighlighted(bool on)
{
	isSelected = on;
	Targetable::setHighlighted(on);
	if (on)
	{
		GameEvents::getInstance().onPawnSelected.broadcast(*this);
	}
	else
	{
		GameEvents::getInstance().onPawnUnselected.broadcast();
		Pawn::selectedPawn = nullptr;
	}
}

void Pawn::setCurrentField(Field* field)
{
	currentField = field;
}

void Pawn::setGameStatePawn(const std::shared_ptr<Game::Pawn>& pawn)
{
	gameStatePawn = pawn;
}

const std::weak_ptr<Game::Pawn>& Pawn::getGameStatePawn() const
{
	return gameStatePawn;
}

Field* Pawn::getCurrentField()
{
	return currentField;
}

void Pawn::onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	bool isHumanControlled = ownerIndex == GameManager::getInstance().getCurrentPlayerIndex() && ownerIndex == GameManager::getInstance().getCurrentPlayerIndex();
	if (!isSelected && isHumanControlled && mouseButton == sf::Mouse::Button::Left)
	{	
		selectedPawn = this;
		setHighlighted(true);
	}
}

void Pawn::onMouseButtonPressed(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	if (isSelected && mouseButton == sf::Mouse::Button::Right)
	{
		selectedPawn = nullptr;
		setHighlighted(false);			
	}
}

void Pawn::onMouseEnter(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	GameEvents::getInstance().onPawnHoverStart.broadcast(*this);
}

void Pawn::onMouseExit(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
{
	GameEvents::getInstance().onPawnHoverEnd.broadcast(*this);
}

