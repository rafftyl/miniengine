#include "Timer.h"

namespace mini
{
	float Time::time;
	float Time::deltaTime;
	clock_t Time::prevTimestamp;

	void Time::updateTimer()
	{
		clock_t currentTimestamp = clock();
		time = static_cast<float>(currentTimestamp) / CLOCKS_PER_SEC;
		deltaTime = static_cast<float>(currentTimestamp - prevTimestamp) / CLOCKS_PER_SEC;
		prevTimestamp = currentTimestamp;
	}

	float Time::getDeltaTime()
	{
		return deltaTime;
	}

	float Time::getTime()
	{
		return time;
	}
}