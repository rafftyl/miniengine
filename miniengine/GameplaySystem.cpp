#include "GameplaySystem.h"
#include "RenderingQueue.h"
#include "InputInterfaces.h"
#include "Collider.h"
#include "Renderer.h"
#include "Camera.h"

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
		GameObject& obj = scenes[currentSceneIndex].addObject(std::move(name));
		obj.setGameplaySystem(shared_from_this());
		return obj;
	}

	GameObject& GameplaySystem::spawnObject(std::string && name, std::function<void(GameObject&)> initFunction)
	{
		GameObject& obj = scenes[currentSceneIndex].addObject(std::move(name));
		initFunction(obj);
		if (!isLoadingScene)
		{
			obj.setGameplaySystem(shared_from_this());
			obj.start();
		}
		return obj;
	}

	void GameplaySystem::destroyObject(GameObject& object)
	{
		if (currentCam != nullptr)
		{
			auto rend = object.getComponent<Renderer>();
			if (rend != nullptr)
			{
				currentCam->unregisterRenderer(rend);
			}
		}
		object.destroy();
		objectsToDestroy.insert(object.getId());		
	}

	void GameplaySystem::loadScene(const std::string& name)
	{	
		isLoadingScene = true;
		if (currentSceneIndex > -1)
		{			
			currentCam = nullptr;
			scenes[currentSceneIndex].unload();
		}

		bool found = false;
		for (size_t i = 0; i < scenes.size() && !found; ++i)
		{
			if (scenes[i].name == name)
			{
				currentSceneIndex = static_cast<int>(i);
				found = true;
			}
		}

		if (!found)
		{
			//TODO: warning
		}
		else
		{
			Scene& currentScene = scenes[currentSceneIndex];
			currentScene.load();
			for (auto& obj : currentScene.objects)
			{
				auto cam = obj.second.getComponent<Camera>();
				if (cam != nullptr)
				{
					currentCam = cam;
					msgBus.engineEvents.onCameraSet.broadcast(currentCam);
				}
			}
			for (auto& obj : currentScene.objects)
			{
				obj.second.setGameplaySystem(shared_from_this());
				obj.second.start();
			}				
		}
		isLoadingScene = false;
	}

	void GameplaySystem::update()
	{
		if (currentCam != nullptr)
		{
			for (auto& obj : scenes[currentSceneIndex].objects)
			{
				obj.second.update();
			}

			for (int id : objectsToDestroy)
			{
				scenes[currentSceneIndex].objects.erase(id);
			}
			objectsToDestroy.clear();
		}
	}

	void GameplaySystem::init()
	{
		registerInputCallbacks();
		if (scenes.size() > 0)
		{
			loadScene(scenes[0].name);
		}		
	}

	std::shared_ptr<Camera> GameplaySystem::getCurrentCam() 
	{
		return currentCam;
	}

	Scene& GameplaySystem::getCurrentScene()
	{
		return scenes[currentSceneIndex];
	}

	void GameplaySystem::closeApplication() const
	{
		msgBus.engineEvents.onEngineShutdownRequest.broadcast();
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

		invokeRaycastCallbacks<input::IMouseButtonPressHandlerRaycast>(
			[&](input::IMouseButtonPressHandlerRaycast& handler)
			{
				handler.onMouseButtonPressedRaycast(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeMouseHoldCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeCallbacks<input::IMouseButtonHoldHandler>(
			[&](input::IMouseButtonHoldHandler& handler)
			{
				handler.onMouseButtonHold(button, mousePosition, mouseDelta);
			});

		invokeRaycastCallbacks<input::IMouseButtonHoldHandlerRaycast>(
			[&](input::IMouseButtonHoldHandlerRaycast& handler)
			{
				handler.onMouseButtonHoldRaycast(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeMouseReleaseCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeCallbacks<input::IMouseButtonReleaseHandler>(
			[&](input::IMouseButtonReleaseHandler& handler)
			{
				handler.onMouseButtonReleased(button, mousePosition, mouseDelta);
			});

		invokeRaycastCallbacks<input::IMouseButtonReleaseHandlerRaycast>(
			[&](input::IMouseButtonReleaseHandlerRaycast& handler)
			{
				handler.onMouseButtonReleasedRaycast(button, mousePosition, mouseDelta);
			}, mousePosition);
	}

	void GameplaySystem::invokeDragStartCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeRaycastCallbacks<input::IMouseDragHandler>(
			[&](input::IMouseDragHandler& handler)
			{
				handler.onMouseDragStart(button, mousePosition, mouseDelta);
				currentDraggedObject = &handler;
			}, mousePosition);
	}

	void GameplaySystem::invokeDragCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		if (currentDraggedObject != nullptr)
		{
			currentDraggedObject->onMouseDrag(button, mousePosition, mouseDelta);
		}
	}

	void GameplaySystem::invokeDragEndCallbacks(sf::Mouse::Button button, const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		invokeRaycastCallbacks<input::IMouseDragHandler>(
			[&](input::IMouseDragHandler& handler)
			{
				handler.onMouseDragEnd(button, mousePosition, mouseDelta);
			}, mousePosition);
		currentDraggedObject = nullptr;
	}

	void GameplaySystem::invokeMouseMoveCallbacks(const sf::Vector2f& mousePosition, const sf::Vector2f& mouseDelta)
	{
		auto moveInterfaces = getAllComponentsOfType<input::IMouseMoveHandler>();
		for (auto& inter : moveInterfaces)
		{
			inter->onMouseMove(mousePosition, mouseDelta);
		}
				
		invokeRaycastCallbacks<input::IMouseMoveHandler>(
			[&](input::IMouseMoveHandler& handler)
			{
				handler.onMouseMove(mousePosition, mouseDelta);
			}, mousePosition);
		
		sf::Vector2f transformedPos = currentCam->screenToWorldPoint(mousePosition);
		auto colliders = getAllComponentsOfType<Collider>();
		for (auto& col : colliders)
		{
			if (col->receivesQueries())
			{
				bool colContainsPointer = col->getOwner().isScreenSpace() ? col->contains(mousePosition) : col->contains(transformedPos);
				auto enterHandler = col->getOwner().getComponent<input::IMouseEnterHandler>();
				if (enterHandler != nullptr && colContainsPointer)
				{
					auto iter = objectsEntered.find(&col->getOwner());
					if (iter == objectsEntered.end())
					{
						objectsEntered.insert(&col->getOwner());
						enterHandler->onMouseEnter(mousePosition, mouseDelta);
					}
				}

				auto exitHandler = col->getOwner().getComponent<input::IMouseExitHandler>();
				if (exitHandler != nullptr && !colContainsPointer)
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