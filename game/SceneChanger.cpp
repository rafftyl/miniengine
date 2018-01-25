#include "SceneChanger.h"
#include "GameplaySystem.h"

SceneChanger::SceneChanger(mini::GameObject& owner) : mini::Component(owner)
{
}

SceneChanger::~SceneChanger()
{
}

void SceneChanger::onKeyPressed(sf::Keyboard::Key key, const mini::ModifierKeys& modifiers)
{
	if (key == sf::Keyboard::Key::Space)
	{
		if (currentScene == "default_scene")
		{
			gameplaySystem->loadScene("other_scene");
			currentScene = "other_scene";
		}
		else
		{
			gameplaySystem->loadScene("default_scene");
			currentScene = "default_scene";
		}
	}
}

