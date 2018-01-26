#pragma once
#include "Component.h"
#include "Renderer.h"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace mini
{
	struct LayoutElementSettings
	{
		bool absolutePositionX = false;
		bool absolutePositionY = false;
		bool absoluteSizeX = false;
		bool absoluteSizeY = false;

		LayoutElementSettings() = default;
		LayoutElementSettings(
			bool absolutePosX, bool absolutePosY,
			bool absoluteSizeX, bool absoluteSizeY) :
			absolutePositionX(absolutePosX), absolutePositionY(absolutePosY),
			absoluteSizeX(absoluteSizeX), absoluteSizeY(absoluteSizeY) {}
	};

	class LayoutElement : public Component
	{
	private:
		LayoutElementSettings settings;
		sf::Vector2f elementPosition;
		sf::Vector2f elementSize;
		sf::Vector2f uniformPivotPosition{ 0.5f, 0.5f };
		std::shared_ptr<Renderer> renderer;
	public:
		LayoutElement(GameObject& owner);
		~LayoutElement();
		void start() override;
		void setPosition(const sf::Vector2f& pos);
		void setSize(const sf::Vector2f& size);
		void setPivotPosition(const sf::Vector2f& position);
		void applySettings(const LayoutElementSettings& layoutSettings);
	};
}
