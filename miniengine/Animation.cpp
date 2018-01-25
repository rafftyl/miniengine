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
	}

	void Animation::reset()
	{
		timer = 0;
		if (loop && timer > loopDuration)
		{
			timer = 0;
		}
	}

	void Animation::setLoopDuration(float duration)
	{
		loopDuration = duration;
	}
}