#include "Collider.h"
namespace mini
{
	Collider::Collider(GameObject& owner) : Component(owner)
	{
	}

	Collider::~Collider()
	{
	}

	bool Collider::isCollisionEnabled() const
	{
		return collisionEnabled;
	}

	bool Collider::receivesQueries() const
	{
		return queriesEnabled;
	}

	void Collider::setCollisionEnabled(bool on)
	{
		collisionEnabled = on;
	}

	void Collider::setQueriesEnabled(bool on)
	{
		queriesEnabled = on;
	}
}