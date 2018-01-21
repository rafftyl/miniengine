#include "GameplaySystem.h"
#include "RenderingQueue.h"
#include "InputInterfaces.h"
#include "Collider.h"
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
		for (size_t i = 0; i < scenes.size()&& !found; ++i)
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
				invokeKeyHoldCallbacks(key, modifiers);
			}
		);

		msgBus.inputEvents.onKeyPress.addCallback(
			[&](sf::Keyboard::Key key, const ModifierKeys& modifiers)
			{
				invokeKeyPressCallbacks(key, modifiers);
			}
		);

		msgBus.inputEvents.onKeyRelease.addCallback(
			[&](sf::Keyboard::Key key, const ModifierKeys& modifiers)
			{
				invokeKeyReleaseCallbacks(key, modifiers);
			}
		);

		msgBus.inputEvents.onMouseButtonPress.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeMousePressCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseButtonHold.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeMouseHoldCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseButtonRelease.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeMouseReleaseCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseDragStart.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeDragStartCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseDragEnd.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeDragEndCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseDrag.addCallback(
			[&](sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeDragCallbacks(button, mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseMove.addCallback(
			[&](const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
			{
				invokeMouseMoveCallbacks(mousePosition, mouseDelta);
			}
		);

		msgBus.inputEvents.onMouseWheelScroll.addCallback(
			[&](float delta)
			{
				invokeMouseWheelCallbacks(delta);
			}
		);
	}

	void GameplaySystem::invokeKeyPressCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers)
	{
		invokeCallbacks<input::IKeyPressHandler>(
			[&](input::IKeyPressHandler& handler)
			{
				handler.onKeyPressed(key, modifiers);
			});
	}

	void GameplaySystem::invokeKeyReleaseCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers)
	{
		invokeCallbacks<input::IKeyReleaseHandler>(
			[&](input::IKeyReleaseHandler& handler)
			{
				handler.onKeyReleased(key, modifiers);
			});
	}
	
	void GameplaySystem::invokeKeyHoldCallbacks(sf::Keyboard::Key key, const ModifierKeys& modifiers)
	{
		invokeCallbacks<input::IKeyHoldHandler>(
			[&](input::IKeyHoldHandler& handler)
			{
				handler.onKeyHold(key, modifiers);
			});
	}

	void GameplaySystem::invokeMousePressCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeCallbacks<input::IMouseButtonPressHandler>(
			[&](input::IMouseButtonPressHandler& handler)
			{
				handler.onMouseButtonPressed(button, mousePosition, mouseDelta);
			});

		invokeRaycastCallbacks<input::raycast::IMouseButtonPressHandler>(
			[&](input::raycast::IMouseButtonPressHandler& handler)
			{
				handler.onMouseButtonPressed(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeMouseHoldCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeCallbacks<input::IMouseButtonHoldHandler>(
			[&](input::IMouseButtonHoldHandler& handler)
			{
				handler.onMouseButtonHold(button, mousePosition, mouseDelta);
			});

		invokeRaycastCallbacks<input::raycast::IMouseButtonHoldHandler>(
			[&](input::raycast::IMouseButtonHoldHandler& handler)
			{
				handler.onMouseButtonHold(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeMouseReleaseCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeCallbacks<input::IMouseButtonReleaseHandler>(
			[&](input::IMouseButtonReleaseHandler& handler)
			{
				handler.onMouseButtonReleased(button, mousePosition, mouseDelta);
			});

		invokeRaycastCallbacks<input::raycast::IMouseButtonReleaseHandler>(
			[&](input::raycast::IMouseButtonReleaseHandler& handler)
			{
				handler.onMouseButtonReleased(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeDragStartCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeRaycastCallbacks<input::raycast::IMouseDragHandler>(
			[&](input::raycast::IMouseDragHandler& handler)
			{
				handler.onMouseDragStart(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeDragCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeRaycastCallbacks<input::raycast::IMouseDragHandler>(
			[&](input::raycast::IMouseDragHandler& handler) 
			{
				handler.onMouseDrag(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeDragEndCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeRaycastCallbacks<input::raycast::IMouseDragHandler>(
			[&](input::raycast::IMouseDragHandler& handler)
			{
				handler.onMouseDragEnd(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeMouseMoveCallbacks(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		auto moveInterfaces = getAllComponentsOfType<input::IMouseMoveHandler>();
		for (auto& inter : moveInterfaces)
		{
			inter->onMouseMove(mousePosition, mouseDelta);
		}

		invokeRaycastCallbacks<input::raycast::IMouseMoveHandler>(
			[&](input::raycast::IMouseMoveHandler& handler)
			{
				handler.onMouseMove(mousePosition, mouseDelta);
			}, mousePosition);


		auto colliders = getAllComponentsOfType<Collider>();
		for (auto& col : colliders)
		{
			if (col->receivesQueries())
			{
				auto enterHandler = col->getOwner().getComponent<input::raycast::IMouseEnterHandler>();
				if (enterHandler != nullptr && col->contains(mousePosition))
				{
					auto iter = objectsEntered.find(&col->getOwner());
					if (iter == objectsEntered.end())
					{
						objectsEntered.insert(&col->getOwner());
						enterHandler->onMouseEnter(mousePosition, mouseDelta);
					}
				}

				auto exitHandler = col->getOwner().getComponent<input::raycast::IMouseExitHandler>();
				if (exitHandler != nullptr && !col->contains(mousePosition))
				{
					auto iter = objectsEntered.find(&col->getOwner());
					if (iter != objectsEntered.end())
					{
						objectsEntered.erase(&col->getOwner());
						exitHandler->onMouseExit(mousePosition, mouseDelta);
					}
				}
			}
		}		
	}

	void GameplaySystem::invokeMouseWheelCallbacks(float delta)
	{
		auto interfaces = getAllComponentsOfType<input::IMouseWheelHandler>();
		for (auto& inter : interfaces)
		{
			inter->onMouseWheel(delta);
		}
	}
}