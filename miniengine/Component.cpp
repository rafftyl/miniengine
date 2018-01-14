#include "Component.h"

namespace mini
{
	Component::Component(GameObject& owner) : owner(owner)
	{
	}


	Component::~Component()
	{
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