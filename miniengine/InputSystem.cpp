#include "InputSystem.h"
#include <SFML/Graphics.hpp>
#include "Time.h"

namespace mini
{
	InputSystem::InputSystem(MessageBus& msgBus, sf::RenderWindow& window) :
		EngineSystem(msgBus), window(window)
	{
	}

	InputSystem::~InputSystem()
	{
	}

	void InputSystem::update()
	{
		EngineSystem::update();
		advanceHoldTimers();
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			switch (sfEvent.type)
			{
			case sf::Event::Closed:
				msgBus.engineEvents.onEngineShutdownRequest.broadcast();
				break;
			case sf::Event::KeyPressed:
				registerKeyPress(sfEvent.key.code, { sfEvent.key.alt, sfEvent.key.control, sfEvent.key.shift });
				break;
			case sf::Event::KeyReleased:
				msgBus.inputEvents.onKeyRelease.broadcast(sfEvent.key.code, { sfEvent.key.alt, sfEvent.key.control, sfEvent.key.shift });
				pressedKeys.erase(sfEvent.key.code);
				break;
			case sf::Event::MouseWheelScrolled:
				handleMouseScroll(sfEvent.mouseWheelScroll.wheel, sfEvent.mouseWheelScroll.delta);
				break;
			case sf::Event::MouseButtonPressed:				
				registerMouseButtonPress(sfEvent.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				msgBus.inputEvents.onMouseButtonRelease.broadcast(sfEvent.mouseButton.button, mousePosition, mouseDelta);
				pressedMouseButtons.erase(sfEvent.mouseButton.button);
				if (isMouseDragging)
				{
					isMouseDragging = false;
					msgBus.inputEvents.onMouseDragEnd.broadcast(sfEvent.mouseButton.button, mousePosition, mouseDelta);
				}
				break;
			case sf::Event::MouseMoved:
				handleMouseMove(sf::Vector2i(sfEvent.mouseMove.x, sfEvent.mouseMove.y));
				break;
			default:
				break;
			}
		}
		broadcastHoldEvents();
	}

	void InputSystem::registerKeyPress(sf::Keyboard::Key key, const ModifierKeys& mods)
	{
		auto iter = pressedKeys.find(key);
		if (iter == pressedKeys.end())
		{
			pressedKeys[key] = 0.0f;
			msgBus.inputEvents.onKeyPress.broadcast(key, mods);
		}
	}

	void InputSystem::registerMouseButtonPress(sf::Mouse::Button button)
	{
		auto iter = pressedMouseButtons.find(button);
		if (iter == pressedMouseButtons.end())
		{
			pressedMouseButtons[button] = 0.0f;
			msgBus.inputEvents.onMouseButtonPress.broadcast(button, mousePosition, mouseDelta);
		}
	}

	void InputSystem::handleMouseMove(const sf::Vector2i& mousePos)
	{
		mouseDelta = sf::Vector2f(static_cast<float>(mousePos.x - mousePosition.x),
								  static_cast<float>(mousePos.y - mousePosition.y));
		mousePosition += mouseDelta;
		msgBus.inputEvents.onMouseMove.broadcast(mousePosition, mouseDelta);

		auto mouseButtonIter = pressedMouseButtons.find(sf::Mouse::Button::Left);
		if (mouseButtonIter != pressedMouseButtons.end())
		{
			if (mouseButtonIter->second > timeToBroadcastDragEvent)
			{
				if (!isMouseDragging)
				{
					isMouseDragging = true;
					msgBus.inputEvents.onMouseDragStart.broadcast(sf::Mouse::Button::Left, mousePosition, mouseDelta);
				}
				else
				{
					msgBus.inputEvents.onMouseDrag.broadcast(sf::Mouse::Button::Left, mousePosition, mouseDelta);
				}
			}
		}
		else
		{
			mouseButtonIter = pressedMouseButtons.find(sf::Mouse::Button::Right);
			if (mouseButtonIter != pressedMouseButtons.end())
			{
				if (!isMouseDragging)
				{
					isMouseDragging = true;
					msgBus.inputEvents.onMouseDragStart.broadcast(sf::Mouse::Button::Right, mousePosition, mouseDelta);
				}
				else
				{
					msgBus.inputEvents.onMouseDrag.broadcast(sf::Mouse::Button::Right, mousePosition, mouseDelta);
				}
			}
		}
	}

	void InputSystem::handleMouseScroll(sf::Mouse::Wheel wheel, float delta)
	{
		if (wheel == sf::Mouse::VerticalWheel)
		{
			msgBus.inputEvents.onMouseWheelScroll.broadcast(delta);
		}
	}

	void InputSystem::advanceHoldTimers()
	{
		for (auto& holdInfo : pressedKeys)
		{
			holdInfo.second += Time::getDeltaTime();
		}

		for (auto& holdInfo : pressedMouseButtons)
		{
			holdInfo.second += Time::getDeltaTime();
		}
	}

	void InputSystem::broadcastHoldEvents() const
	{
		for (const auto& holdInfo : pressedKeys)
		{
			if (holdInfo.second > timeToBroadcastHoldEvent)
			{				
				bool alt = (pressedKeys.find(sf::Keyboard::LAlt) != pressedKeys.end()) ||
						   (pressedKeys.find(sf::Keyboard::RAlt) != pressedKeys.end());
				bool ctrl = (pressedKeys.find(sf::Keyboard::LControl) != pressedKeys.end()) ||
							(pressedKeys.find(sf::Keyboard::RControl) != pressedKeys.end());
				bool shift = (pressedKeys.find(sf::Keyboard::LShift) != pressedKeys.end()) ||
					(pressedKeys.find(sf::Keyboard::RShift) != pressedKeys.end());
				msgBus.inputEvents.onKeyHold.broadcast(holdInfo.first, { alt, ctrl, shift });
			}
		}

		for (const auto& holdInfo : pressedMouseButtons)
		{
			if (holdInfo.second > timeToBroadcastHoldEvent)			
			{
				msgBus.inputEvents.onMouseButtonHold.broadcast(holdInfo.first, mousePosition, mouseDelta);
			}
		}
	}
}
