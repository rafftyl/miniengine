#pragma once
#include "Event.h"

class GameEvents 
{
public:
	static GameEvents& getInstance()
	{
		static GameEvents instance;
		return instance;
	}

	mini::Event<class Pawn&> onPawnSelected;
	mini::Event<> onPawnUnselected;
	mini::Event<> onTurnFinished;

	void clearEvents();
private:
	GameEvents();
	~GameEvents();
};

