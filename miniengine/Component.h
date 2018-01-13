#pragma once
namespace mini
{
	class Component
	{
	protected:
		class GameObject& owner;
	public:
		Component(GameObject& owner);
		virtual ~Component();

		virtual void update(float deltaTime) = 0;

		template<class ComponentType>
		bool isOfType() const
		{
			return dynamic_cast<const ComponentType*>(this) != nullptr;
		}
	};
}
