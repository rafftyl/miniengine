#pragma once
#include "Collider.h"

namespace mini
{
	class BoxCollider : public Collider
	{
	private:
		sf::Vector2f size;
		sf::Vector2f offset;
	public:
		BoxCollider(GameObject& owner);
		virtual ~BoxCollider();
		void setSize(const sf::Vector2f& inSize);
		void setOffset(const sf::Vector2f& inOffset);
		virtual bool contains(const sf::Vector2f& point) const override;
	};
}
