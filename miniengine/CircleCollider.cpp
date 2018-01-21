#include "CircleCollider.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iostream>

namespace mini
{
	CircleCollider::CircleCollider(GameObject& owner) : Collider(owner)
	{
		auto rend = owner.getComponent<Renderer>();
		if (rend != nullptr)
		{
			sf::Vector2f min, max;
			rend->getLocalBounds(min, max);
			radius = 0.5f * std::max(max.x - min.x, max.y - min.y);
			center = 0.5f * (min + max);
		}
	}

	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::setRadius(float inRadius)
	{
		radius = inRadius;
	}

	void CircleCollider::setCenter(const sf::Vector2f& inCenter)
	{
		center = inCenter;
	}

	bool CircleCollider::contains(const sf::Vector2f& point) const
	{
		sf::Vector2f globalCenter = owner.getTransform() * center;
		float scaledRad = radius * owner.getScale().x;
		return point.distance(globalCenter) < scaledRad;
	}
}