#pragma once
#include "GameObject.h"
#include <map>
#include <string>
#include <functional>

namespace mini
{
	class Scene
	{
		friend class GameplaySystem;
	private:
		std::string name;
		unsigned int nextId = 0;
		std::map<unsigned int, GameObject> objects;
		std::function<void(Scene&)> initScene;
	public:
		Scene(std::string&& name, std::function<void(Scene&)> initializationRoutine);
		~Scene();
		GameObject& addObject(std::string&& name);
		const std::string& getName() const;
		void load();
		void unload();
	};
}
