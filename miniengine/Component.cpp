#include "Component.h"

namespace mini
{
	Component::Component(GameObject& owner) : owner(owner)
	{
	}


	Component::~Component()
	{
	}

	const GameObject& Component::getOwner() const
	{
		return owner;
	}

	GameObject& Component::getOwner()
	{
		return owner;
	}

	GameplaySystem& Component::getGameplaySystem()
	{
		return *gameplaySystem;
	}

	void Component::start()
	{
	}

	void Component::update()
	{
	}

	void Component::destroy()
	{
	}
}