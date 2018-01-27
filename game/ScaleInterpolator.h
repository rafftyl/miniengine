#pragma once
#include "VectorInterpolator.h"
class ScaleInterpolator :
	public VectorInterpolator
{
public:
	ScaleInterpolator(mini::GameObject& owner);
	~ScaleInterpolator();

	// Inherited via VectorInterpolator
	virtual void applyVector(mini::GameObject& object, sf::Vector2f vec) override;
};

