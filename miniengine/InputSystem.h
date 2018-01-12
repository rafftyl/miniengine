#pragma once
#include "EngineSystem.h"
namespace sf { class RenderWindow; }
class InputSystem : public EngineSystem
{
private:
	sf::RenderWindow& window;
public:
	InputSystem(MessageBus& msgBus, sf::RenderWindow& window);
	virtual ~InputSystem();

	virtual void update() override;
};

