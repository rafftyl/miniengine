#include "DebugConsole.h"
#include <iostream>

namespace mini
{
	DebugConsole::DebugConsole(MessageBus& msgBus) : EngineSystem(msgBus)
	{
		msgBus.inputEvents.onMouseDrag.addCallback(
		[&](sf::Mouse::Button button, const sf::Vector2i& pos, const sf::Vector2f& delta) 
		{
			std::cout << "Mouse drag button: " << button << "pos: " << pos.x << " " << pos.y << " delta: " << delta.x << " " << delta.y << std::endl;
		});

		msgBus.inputEvents.onMouseDragStart.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2i& pos, const sf::Vector2f& delta)
		{
			std::cout << "Mouse drag start"<< std::endl;
		});

		msgBus.inputEvents.onMouseDragEnd.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2i& pos, const sf::Vector2f& delta)
		{
			std::cout << "Mouse drag end" << std::endl;
		});

		msgBus.inputEvents.onKeyPress.addCallback(
		[&](sf::Keyboard::Key key, const ModifierKeys& mods)
		{
			std::cout << "key pressed: " << key << mods.alt << mods.ctrl << mods.shift << std::endl;
		});

		msgBus.inputEvents.onKeyHold.addCallback(
		[&](sf::Keyboard::Key key, const ModifierKeys& mods)
		{
			std::cout << "key hold: " << key << mods.alt << mods.ctrl << mods.shift << std::endl;
		});
	}

	DebugConsole::~DebugConsole()
	{
	}
}