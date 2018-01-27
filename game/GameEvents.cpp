#include "GameEvents.h"

void GameEvents::clearEvents()
{
	onPawnSelected.clear();
	onPawnUnselected.clear();
	onTurnFinished.clear();
}

GameEvents::GameEvents()
{
}


GameEvents::~GameEvents()
{
}
