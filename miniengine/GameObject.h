#pragma once
#include "Component.h"
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <memory>
#include <string>

namespace mini
{
	class GameObject : public sf::Transformable
	{
		friend class GameplaySystem;
	private:
		std::shared_ptr<GameplaySystem> gameplaySystem;
		std::vector<std::shared_ptr<Component>> components;
		unsigned int id = 0;
		std::string name;
		bool active = true;
	public:
		GameObject(unsigned int id = 0);
		GameObject(std::string&& name, unsigned int id = 0);
		~GameObject();
		int getId() const;
		const std::string& getName() const;
		bool isActive() const;
		void setActive(bool on);

		template<class ComponentType>
		std::shared_ptr<ComponentType> getComponent() 
		{
			for (const auto& comp : components)
			{
				if (comp->isOfType<ComponentType>())
				{
					return std::dynamic_pointer_cast<ComponentType>(comp);
				}
			}
			return nullptr;
		}

		template<class ComponentType>
		ComponentType& addComponent()
		{
			auto newComp = std::make_shared<ComponentType>(*this);
			components.push_back(newComp);
			if (gameplaySystem != nullptr)
			{
				newComp->gameplaySystem = gameplaySystem;			
				newComp->start();
			}
			return *newComp;
		}

	private:
		void start();
		void update();
		void destroy();		
		void setGameplaySystem(const std::shared_ptr<GameplaySystem>& system);
	};
}