#pragma once
#include "Component.h"
#include "InputInterfaces.h"

class SceneChanger : public mini::Component, public mini::input::IKeyPressHandler
{
public:
	std::string currentScene = "";
public:
	SceneChanger(mini::GameObject& owner);
	~SceneChanger();
	virtual void onKeyPressed(sf::Keyboard::Key key, const mini::ModifierKeys& modifiers) override;
};

