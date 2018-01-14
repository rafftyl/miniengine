#include "GameObject.h"

namespace mini
{
	GameObject::GameObject(unsigned int id) : GameObject("Game Object", id)
	{
	}

	GameObject::GameObject(std::string&& name, unsigned int id) : name(std::move(name)), id(id)
	{
	}

	GameObject::~GameObject()
	{
	}

	int GameObject::getId() const
	{
		return id;
	}

	const std::string & GameObject::getName() const
	{
		return name;
	}

	bool GameObject::isActive() const
	{
		return active;
	}

	void GameObject::setActive(bool on)
	{
		active = on;
	}

	void GameObject::start()
	{
		for (const auto& comp : components)
		{
			comp->start();
		}
	}

	void GameObject::update()
	{
		for (const auto& comp : components)
		{
			comp->update();
		}
	}

	void GameObject::destroy()
	{
		for (const auto& comp : components)
		{
			comp->destroy();
		}
	}

	void GameObject::setGameplaySystem(const std::shared_ptr<GameplaySystem>& system)
	{
		gameplaySystem = system;
		for (const auto& comp : components)
		{
			comp->gameplaySystem = gameplaySystem;
		}
	}
}