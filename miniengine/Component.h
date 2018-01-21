#pragma once
#include <memory>
namespace mini
{
	class Component
	{
		friend class GameObject;
	protected:
		class GameObject& owner;
		std::shared_ptr<class GameplaySystem> gameplaySystem;
	public:
		Component(GameObject& owner);
		virtual ~Component();
		const GameObject& getOwner() const;
		GameObject& getOwner();

		template<class ComponentType>
		bool isOfType() const
		{
			return dynamic_cast<const ComponentType*>(this) != nullptr;
		}

	protected:
		virtual void start();
		virtual void update();
		virtual void destroy();
	};
}
