#include "GameEvents.h"

void GameEvents::clearEvents()
{
	onPawnSelected.clear();
	onPawnUnselected.clear();
	onTurnFinished.clear();
	onGameStateChanged.clear();
}

GameEvents::GameEvents()
{
}


GameEvents::~GameEvents()
{
}
