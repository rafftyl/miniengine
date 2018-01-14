#pragma once
#include "EngineSystem.h"
#include "Scene.h"

namespace mini
{
	class GameplaySystem : public EngineSystem, public std::enable_shared_from_this<GameplaySystem>
	{
	private:
		std::vector<Scene> scenes;
		size_t currentSceneIndex = 0;
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
		void sendKeyHoldCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers);
		void sendMouseHoldCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta);
	};
}
