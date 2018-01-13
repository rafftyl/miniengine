// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Miniengine.h>

int main()
{
	mini::EngineSettings settings;
	settings.windowHeight = 480;
	settings.windowWidth = 640;
	settings.windowName = "Example Game";
	mini::Miniengine engine(settings);
	engine.Run();
	return 0;
}

