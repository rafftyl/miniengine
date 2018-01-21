#pragma once
#include "Collider.h"

namespace mini
{
	class CircleCollider : public Collider
	{
	private:
		sf::Vector2f center;
		float radius;
	public:
		CircleCollider(GameObject& owner);
		virtual ~CircleCollider();
		void setRadius(float inRadius);
		void setCenter(const sf::Vector2f& inCenter);
		virtual bool contains(const sf::Vector2f & point) const override;
	};
}
