#pragma once
#include "Component.h"
#include "Renderer.h"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace mini
{
	class LayoutElement : public Component
	{
	private:
		sf::Vector2f uniformPosition;
		sf::Vector2f elementSize;
		sf::Vector2f uniformPivotPosition;
		std::shared_ptr<Renderer> renderer;
		bool absoluteSize = true;
	public:
		LayoutElement(GameObject& owner);
		~LayoutElement();
		void start() override;
		void setUniformPosition(const sf::Vector2f& pos);
		void setUniformSize(const sf::Vector2f& size);
		void setAbsoluteSize(const sf::Vector2f& size);
		void setPivotPosition(const sf::Vector2f& position);
	};
}
