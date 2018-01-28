#pragma once
#include "Event.h"
#include "GameState/GameState.h"

class GameEvents 
{
public:
	static GameEvents& getInstance()
	{
		static GameEvents instance;
		return instance;
	}

	mini::Event<class Pawn&> onPawnSelected;
	mini::Event<class Pawn&> onPawnHoverStart;
	mini::Event<class Pawn&> onPawnHoverEnd;
	mini::Event<> onPawnUnselected;
	mini::Event<> onTurnFinished;
	mini::Event<Game::GameState&> onGameStateChanged;
	void clearEvents();
private:
	GameEvents();
	~GameEvents();
};

