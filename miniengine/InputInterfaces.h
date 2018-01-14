#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/System/Vector2.hpp"
#include "ModifierKeys.h"
#include <set>

namespace mini
{
	namespace input
	{
		class IKeyPressHandler
		{
		public:
			virtual void onKeyPressed(sf::Keyboard::Key key, const ModifierKeys& modifiers) = 0;
		};

		class IKeyReleaseHandler
		{
		public:
			virtual void onKeyReleased(sf::Keyboard::Key key, const ModifierKeys& modifiers) = 0;
		};

		class IKeyHoldHandler
		{
		public:
			virtual void onKeyHold(sf::Keyboard::Key key, const ModifierKeys& modifiers) = 0;
		};
		class IMouseButtonPressHandler
		{
		public:
			virtual void onMouseButtonPressed(
				sf::Mouse::Button mouseButton,
				const sf::Vector2f& mousePosition,
				const sf::Vector2f& mouseDelta) = 0;
		};

		class IMouseButtonReleaseHandler
		{
		public:
			virtual void onMouseButtonReleased(
				sf::Mouse::Button mouseButton,
				const sf::Vector2f& mousePosition,
				const sf::Vector2f& mouseDelta) = 0;
		};

		class IMouseButtonHoldHandler
		{
		public:
			virtual void onMouseButtonHold(
				sf::Mouse::Button mouseButton,
				const sf::Vector2f& mousePosition,
				const sf::Vector2f& mouseDelta) = 0;
		};			

		class IMouseWheelHandler
		{
		public:
			virtual void onMouseWheel(float delta) = 0;
		};		

		class IMouseMoveHandler
		{
		public:
			virtual void onMouseMove(
				const sf::Vector2f& mousePosition,
				const sf::Vector2f& mouseDelta) = 0;
		};		

		namespace raycast
		{
			class IMouseButtonPressHandler
			{
			public:
				virtual void onMouseButtonPressed(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseButtonReleaseHandler
			{
			public:
				virtual void onMouseButtonReleased(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseButtonHoldHandler
			{
			public:
				virtual void onMouseButtonHold(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseDragHandler
			{
			public:
				virtual void onMouseDragStart(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;

				virtual void onMouseDragEnd(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;

				virtual void onMouseDrag(
					sf::Mouse::Button mouseButton,
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseMoveHandler
			{
			public:
				virtual void onMouseMove(
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseEnterHandler
			{
				virtual void onMouseEnter(
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};

			class IMouseExitHandler
			{
				virtual void onMouseExit(
					const sf::Vector2f& mousePosition,
					const sf::Vector2f& mouseDelta) = 0;
			};
		}
	}	
}