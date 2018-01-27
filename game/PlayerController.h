#pragma once
#include "Component.h"

class PlayerController : public mini::Component
{
public:
	PlayerController(mini::GameObject& owner);
	virtual ~PlayerController();
	virtual void startTurn() = 0;
	virtual void endTurn() = 0;
};

