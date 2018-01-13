#pragma once
#include "Component.h"
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <memory>

namespace mini
{
	class GameObject : public sf::Transformable
	{
	private:
		std::vector<std::shared_ptr<Component>> components;
	public:
		GameObject();
		~GameObject();

		template<class ComponentType>
		std::shared_ptr<ComponentType> getComponent()
		{
			for (const auto& comp : components)
			{
				if (comp->isOfType<ComponentType>())
				{
					return std::static_pointer_cast<ComponentType>(comp);
				}
			}
			return nullptr;
		}

		template<class ComponentType>
		ComponentType& addComponent()
		{
			auto newComp = std::make_shared<ComponentType>(*this);
			components.push_back(newComp);
			return *newComp;
		}
	};
}
