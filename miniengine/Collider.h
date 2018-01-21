#pragma once
#include "Component.h"
#include "SFML/System/Vector2.hpp"
namespace mini
{
	class Collider : public Component
	{
	private:
		bool collisionEnabled = true;
		bool queriesEnabled = true;
	public:
		Collider(GameObject& owner);
		virtual ~Collider();
		virtual bool contains(const sf::Vector2f& point) const = 0;
		bool isCollisionEnabled() const;
		bool receivesQueries() const;
		void setCollisionEnabled(bool on);
		void setQueriesEnabled(bool on);

		//TODO: collisions and intersections
	};
}
