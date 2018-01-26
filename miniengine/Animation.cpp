#include "Animation.h"

namespace mini
{
	Animation::Animation(bool shouldLoop) : loop(shouldLoop)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::update(float deltaTime)
	{
		timer += deltaTime;
		if (loop && timer > loopDuration)
		{
			timer = 0;
		}
	}

	void Animation::reset()
	{
		timer = 0;
	}

	bool Animation::isFinished() const
	{
		return !loop && timer >= loopDuration;
	}

	void Animation::setLoopDuration(float duration)
	{
		loopDuration = duration;
	}
}