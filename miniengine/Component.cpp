#include "Component.h"

namespace mini
{
	Component::Component(GameObject& owner) : owner(owner)
	{
	}


	Component::~Component()
	{
	}
}