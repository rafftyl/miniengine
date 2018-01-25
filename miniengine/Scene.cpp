#include "Scene.h"

namespace mini
{
	Scene::Scene(std::string&& name, std::function<void(Scene&)> initializationRoutine) : 
		name(std::move(name)), initScene(initializationRoutine)
	{
	}

	Scene::~Scene()
	{
	}

	GameObject& Scene::addObject(std::string&& name)
	{
		auto itr = objects.insert(std::make_pair(nextId, GameObject(std::move(name), nextId)));
		++nextId;
		return itr.first->second;
	}

	void Scene::load()
	{
		initScene(*this);
	}

	void Scene::unload()
	{
		for (auto& obj : objects)
		{
			obj.second.destroy();
		}
		objects.clear();
	}
}