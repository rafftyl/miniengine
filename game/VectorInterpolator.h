#pragma once
#include "Component.h"
#include "Event.h"
#include "SFML/System/Vector2.hpp"
#include <queue>

class VectorInterpolator :
	public mini::Component
{
private:
	float timer = 0;
	float intervalStart = 0;
	float intervalEnd = 0;
	bool isMoving = false;

	sf::Vector2f segmentStart;
	sf::Vector2f segmentEnd;

	std::queue<std::pair<float, sf::Vector2f>> waypoints;
	mini::Event<> onMovementFinishedEvent;
public:
	VectorInterpolator(mini::GameObject& owner);
	virtual ~VectorInterpolator();
	void update() override;
	void startMovement(std::queue<std::pair<float, sf::Vector2f>>&& path);
	mini::Event<>& onMovementFinished();
protected:
	virtual void applyVector(mini::GameObject& object, sf::Vector2f vec) = 0;
};

