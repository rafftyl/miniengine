#include "BoxCollider.h"
#include "Renderer.h"
#include "GameObject.h"

namespace mini
{
	BoxCollider::BoxCollider(GameObject& owner) : Collider(owner)
	{
		auto rend = owner.getComponent<Renderer>();
		if (rend != nullptr)
		{
			sf::Vector2f min, max;
			rend->getLocalBounds(min, max);
			size = max - min;
			offset = 0.5f * (min + max);
		}
	}

	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::setSize(const sf::Vector2f & inSize)
	{
		size = inSize;
	}

	void BoxCollider::setOffset(const sf::Vector2f& inOffset)
	{
		offset = inOffset;
	}

	bool BoxCollider::contains(const sf::Vector2f& point) const
	{
		sf::Vector2f scaledSize(owner.getScale().x * size.x, owner.getScale().y * size.y);
		sf::Vector2f min = offset - 0.5f * scaledSize;
		sf::Vector2f max = offset + 0.5f * scaledSize;
		min += owner.getPosition();
		max += owner.getPosition();
		return point.x > min.x && point.y > min.y && point.x < max.x && point.y < max.y;
	}
}