#pragma once
#include "GameObject.h"
#include <map>
#include <string>

namespace mini
{
	class Scene
	{
		friend class GameplaySystem;
	private:
		std::string name;
		unsigned int nextId = 0;
		std::map<unsigned int, GameObject> objects;
	public:
		Scene(std::string&& name);
		~Scene();
		GameObject& addObject(std::string&& name);
	};
}
