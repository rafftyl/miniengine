#include "GameEvents.h"

void GameEvents::clearEvents()
{
	onPawnSelected.clear();
	onPawnUnselected.clear();
	onTurnFinished.clear();
	onGameStateChanged.clear();
	onPawnHoverStart.clear();
	onPawnHoverEnd.clear();
}

GameEvents::GameEvents()
{
}


GameEvents::~GameEvents()
{
}
