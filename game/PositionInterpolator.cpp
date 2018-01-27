#include "PositionInterpolator.h"
#include "GameObject.h"

PositionInterpolator::PositionInterpolator(mini::GameObject& owner) : VectorInterpolator(owner)
{
}

PositionInterpolator::~PositionInterpolator()
{
}

void PositionInterpolator::applyVector(mini::GameObject& object, sf::Vector2f vec)
{
	object.setPosition(vec);
}
