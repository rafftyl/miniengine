#pragma once
#include "VectorInterpolator.h"
class PositionInterpolator :
	public VectorInterpolator
{
public:
	PositionInterpolator(mini::GameObject& owner);
	~PositionInterpolator();

	// Inherited via VectorInterpolator
	virtual void applyVector(mini::GameObject& object, sf::Vector2f vec) override;
};

