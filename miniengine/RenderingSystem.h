#pragma once
#include "EngineSystem.h"
#include <memory>

namespace sf { class RenderWindow; }
class RenderingSystem : public EngineSystem
{
private:
	sf::RenderWindow& window;
public:
	RenderingSystem(MessageBus& msgBus, sf::RenderWindow& window);
	virtual ~RenderingSystem();

	virtual void update() override;
};

