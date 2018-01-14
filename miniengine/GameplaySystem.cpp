#include "GameplaySystem.h"
#include "RenderingQueue.h"
#include "InputInterfaces.h"
#include "Renderer.h"

namespace mini
{
	GameplaySystem::GameplaySystem(MessageBus& msgBus, std::vector<Scene>&& scenes) : 
		EngineSystem(msgBus), scenes(std::move(scenes))
	{
	}

	GameplaySystem::~GameplaySystem()
	{
	}

	GameObject& GameplaySystem::spawnObject(std::string&& name)
	{
		return scenes[currentSceneIndex].addObject(std::move(name));
	}

	void GameplaySystem::destroyObject(GameObject& object)
	{
		scenes[currentSceneIndex].objects.erase(object.getId());
	}

	void GameplaySystem::loadScene(const std::string& name)
	{	
		for (auto& obj : scenes[currentSceneIndex].objects)
		{
			obj.second.destroy();
		}

		bool found = false;
		for (size_t i = 0; i < scenes.size() && !found; ++i)
		{
			if (scenes[i].name == name)
			{
				currentSceneIndex = i;
				found = true;
			}
		}

		if (!found)
		{
			//TODO: warning
		}
		else
		{
			for (auto& obj : scenes[currentSceneIndex].objects)
			{
				obj.second.start();
			}
		}
	}

	void GameplaySystem::update()
	{
		RenderingQueue renderingQueue;
		for (auto& obj : scenes[currentSceneIndex].objects)
		{
			obj.second.update();
			auto rend = obj.second.getComponent<Renderer>();
			if (rend != nullptr)
			{
				//TODO: culling
				renderingQueue.push(rend);
			}
		}
		msgBus.engineEvents.onCreateRenderingQueue.broadcast(renderingQueue);
	}

	void GameplaySystem::init()
	{
		for (auto& scene : this->scenes)
		{
			for (auto& obj : scene.objects)
			{
				obj.second.setGameplaySystem(shared_from_this());
			}
		}
		registerInputCallbacks();

		currentSceneIndex = 0;
		for (auto& obj : scenes[currentSceneIndex].objects)
		{
			obj.second.start();
		}
	}

	void GameplaySystem::registerInputCallbacks()
	{
		msgBus.inputEvents.onKeyHold.addCallback(
			[&](sf::Keyboard::Key key, const ModifierKeys& modifiers)
			{
				sendKeyHoldCallbacks(key, modifiers);
			}
		);

		msgBus.inputEvents.onMouseButtonHold.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				sendMouseHoldCallbacks(button, mousePosition, mouseDelta);
			}
		);

		//TODO: implement all callbacks
	}
	
	//TODO: optimize passing events (avoid iterating over all objects - first register interfaces, than iterate over them)
	void GameplaySystem::sendKeyHoldCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers)
	{
		for (auto& obj : scenes[currentSceneIndex].objects)
		{
			auto handler = obj.second.getComponent<input::IKeyHoldHandler>();
			if (handler != nullptr)
			{
				handler->onKeyHold(key, modifiers);
			}
		}
	}

	void GameplaySystem::sendMouseHoldCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		for (auto& obj : scenes[currentSceneIndex].objects)
		{
			auto handler = obj.second.getComponent<input::IMouseButtonHoldHandler>();
			if (handler != nullptr)
			{
				handler->onMouseButtonHold(button, mousePosition, mouseDelta);
			}
		}
	}
}