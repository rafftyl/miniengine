#pragma once
#include "Component.h"
#include "InputInterfaces.h"

class KeyMover : public mini::Component, public mini::input::IKeyHoldHandler, public mini::input::IMouseWheelHandler
{
public:
	KeyMover(mini::GameObject& owner);
	~KeyMover();
	virtual void onKeyHold(sf::Keyboard::Key key, const mini::ModifierKeys& modifiers) override;
	virtual void onMouseWheel(float delta) override;
};

