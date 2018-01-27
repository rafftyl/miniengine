#pragma once
#include <functional>
#include <string>
#include <sstream>
#include "GameObject.h"
#include "Scene.h"

namespace mini
{
	class Prefab
	{
	private:
		std::string name;
		int instanceCounter = 0;
		std::function<void(GameObject&)> initFunction;
	public:
		Prefab() = default;
		Prefab(const std::string& name, std::function<void(GameObject&)> initFunction);
		~Prefab();

		GameObject& instantiate(Scene& scene);
		GameObject& instantiate(GameplaySystem& gameplaySystem);
	};
}

