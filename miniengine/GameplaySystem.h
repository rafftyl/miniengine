#pragma once
#include "EngineSystem.h"
#include "Scene.h"
#include <set>

namespace mini
{
	class GameplaySystem : public EngineSystem, public std::enable_shared_from_this<GameplaySystem>
	{
	private:
		std::vector<Scene> scenes;
		size_t currentSceneIndex = 0;

		//TODO: move to a separate InputEventSystem class
		std::set<const GameObject*> objectsEntered;
	public:
		GameplaySystem(MessageBus& msgBus, std::vector<Scene>&& scenes);
		virtual ~GameplaySystem();

		GameObject& spawnObject(std::string&& name);
		void destroyObject(GameObject& object);
		void loadScene(const std::string& name);
		virtual void update() override;
		virtual void init() override;

	private:
		void registerInputCallbacks();
		//TODO: move all these methods to a separate InputEventSystem class
		void invokeKeyPressCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers);
		void invokeKeyReleaseCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers);
		void invokeKeyHoldCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers);
		void invokeMousePressCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeMouseHoldCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeMouseReleaseCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeDragStartCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeDragCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeDragEndCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeMouseMoveCallbacks(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
		void invokeMouseWheelCallbacks(float delta);

		//TODO: create an analogous method in InputEventSystem class
		template<class ComponentType>
		std::vector<std::shared_ptr<ComponentType>> getAllComponentsOfType()
		{
			std::vector<std::shared_ptr<ComponentType>> result;
			for (auto& obj : scenes[currentSceneIndex].objects)
			{
				auto comp = obj.second.getComponent<ComponentType>();
				if (comp != nullptr)
				{
					result.push_back(comp);
				}
			}
			return result;
		}

		//TODO: move these methods to a separate InputEventSystem class
		template<class InterfaceType>
		void invokeCallbacks(std::function<void(InterfaceType&)> fun)
		{
			auto interfaces = getAllComponentsOfType<InterfaceType>();
			for (auto& inter : interfaces)
			{
				fun(*inter);
			}
		}

		template<class RaycastInterfaceType>
		void invokeRaycastCallbacks(std::function<void(RaycastInterfaceType&)> fun, const sf::Vector2f& mousePosition)
		{
			auto colliders = getAllComponentsOfType<Collider>();
			for (auto& col : colliders)
			{
				if (col->receivesQueries())
				{
					auto inter = col->getOwner().getComponent<RaycastInterfaceType>();
					if (inter != nullptr && col->contains(mousePosition))
					{
						fun(*inter);
					}
				}
			}
		}
	};
}
