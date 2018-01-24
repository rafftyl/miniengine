#pragma once
#include <ctime>

namespace mini
{
	class Time
	{
		friend class Miniengine;
	private:
		static clock_t prevTimestamp;
		static float deltaTime;
		static float time;
		static void updateTimer();
	public:
		static float getDeltaTime();
		static float getTime();		
	};
}