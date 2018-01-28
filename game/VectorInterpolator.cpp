#include "VectorInterpolator.h"
#include "Timer.h"
#include "GameObject.h"

VectorInterpolator::VectorInterpolator(mini::GameObject& owner) : mini::Component(owner)
{
}

VectorInterpolator::~VectorInterpolator()
{
}

void VectorInterpolator::update()
{
	if (isMoving)
	{
		timer += mini::Time::getDeltaTime();
		if (timer >= intervalEnd)
		{
			if (waypoints.size() == 0)
			{
				applyVector(owner, segmentEnd);
				onMovementFinishedEvent.broadcast();
				isMoving = false;
				return;
			}
			intervalStart = intervalEnd;
			intervalEnd = waypoints.front().first;
			segmentStart = segmentEnd;
			segmentEnd = waypoints.front().second;
			waypoints.pop();
		}
		applyVector(owner, segmentStart + (timer - intervalStart) / (intervalEnd - intervalStart) * (segmentEnd - segmentStart));
	}
}

void VectorInterpolator::startMovement(std::queue<std::pair<float, sf::Vector2f>>&& path)
{
	waypoints = std::move(path);
	intervalStart = 0;
	intervalEnd = waypoints.front().first;
	timer = 0;
	segmentStart = owner.getPosition();
	segmentEnd = waypoints.front().second;
	waypoints.pop();
	isMoving = true;
}

mini::Event<>& VectorInterpolator::onMovementFinished()
{
	return onMovementFinishedEvent;
}
