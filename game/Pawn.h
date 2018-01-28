#pragma once
#include "Targetable.h"
#include "InputInterfaces.h"
#include "Renderer.h"
#include "GameState/Pawn.h"

class Pawn : 
	public Targetable, 
	public mini::input::IMouseButtonPressHandlerRaycast,
	public mini::input::IMouseButtonPressHandler
{
public:
	static Pawn* selectedPawn;
private:
	class Field* currentField = nullptr;
	bool isSelected = false;
	int ownerIndex = 0;
	std::weak_ptr<Game::Pawn> gameStatePawn;
public:
	Pawn(mini::GameObject& owner);
	~Pawn();
	void start() override;
	void setOwnerIndex(int index);
	int getOwnerIndex() const;
	void setHighlighted(bool on) override;
	void setCurrentField(Field* field);
	void setGameStatePawn(const std::shared_ptr<Game::Pawn>& pawn);
	const std::weak_ptr<Game::Pawn>& getGameStatePawn() const;
	Field* getCurrentField();
	// Inherited via IMouseButtonPressHandlerRaycast
	virtual void onMouseButtonPressedRaycast(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
	// Inherited via IMouseButtonPressHandler
	virtual void onMouseButtonPressed(sf::Mouse::Button mouseButton, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta) override;
};


