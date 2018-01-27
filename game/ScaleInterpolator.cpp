#include "ScaleInterpolator.h"
#include "GameObject.h"

ScaleInterpolator::ScaleInterpolator(mini::GameObject& owner) : VectorInterpolator(owner)
{
}

ScaleInterpolator::~ScaleInterpolator()
{
}

void ScaleInterpolator::applyVector(mini::GameObject& object, sf::Vector2f vec)
{
	object.setScale(vec);
}
