#include "Prefab.h"
#include "GameplaySystem.h"

namespace mini
{
	Prefab::Prefab(const std::string& name, std::function<void(GameObject&)> initFunction) : name(name), initFunction(initFunction)
	{
	}

	Prefab::~Prefab()
	{
	}

	GameObject& Prefab::instantiate(Scene& scene)
	{
		std::stringstream ss;
		ss << name << "_" << instanceCounter++;
		GameObject& object = scene.addObject(ss.str());
		initFunction(object);
		return object;
	}

	GameObject& Prefab::instantiate(GameplaySystem& gameplaySystem)
	{
		std::stringstream ss;
		ss << name << "_" << instanceCounter++;
		GameObject& object = gameplaySystem.spawnObject(ss.str(), initFunction);
		return object;
	}
}