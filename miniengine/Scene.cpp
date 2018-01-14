#include "Scene.h"

namespace mini
{
	Scene::Scene(std::string&& name) : name(std::move(name))
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
}