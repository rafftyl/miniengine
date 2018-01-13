#pragma once
#include "Event.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/System/Vector2.hpp"
#include <set>

namespace mini
{
	struct ModifierKeys
	{
		bool alt;
		bool ctrl;
		bool shift;
	};

	typedef Event<> BasicEvent;
	typedef Event<sf::Keyboard::Key, const ModifierKeys&> KeyboardEvent;
	typedef Event<sf::Mouse::Button, const sf::Vector2f&, const sf::Vector2f&> MouseEvent;

	struct EngineEvents
	{
		BasicEvent onEngineStart;
		BasicEvent onEngineShutdownRequest;
		BasicEvent onEngineShutdown;
	};

	struct InputEvents
	{
		KeyboardEvent onKeyPress;
		KeyboardEvent onKeyRelease;
		KeyboardEvent onKeyHold;
		MouseEvent onMouseMove;
		MouseEvent onMouseButtonPress;
		MouseEvent onMouseButtonRelease;
		MouseEvent onMouseButtonHold;
		Event<float>  onMouseWheelScroll;
		MouseEvent onMouseDragStart;
		MouseEvent onMouseDragEnd;
		MouseEvent onMouseDrag;
	};

	class MessageBus
	{
	public:
		EngineEvents engineEvents;
		InputEvents inputEvents;
	public:
		MessageBus();
		~MessageBus();
	};
}
