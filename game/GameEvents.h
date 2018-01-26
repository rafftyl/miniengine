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
	mini::Event<> onPlayerFinishedMove;
private:
	GameEvents();
	~GameEvents();
};

