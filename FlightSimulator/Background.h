#pragma once

#include "FlightSim.h"

class Background
{
public:
	bool enableFog;

	Background()
	{
		enableFog = false;
	}

	inline void switchEnableFogTag()
	{
		enableFog = !enableFog;
	}

	void createScene();
	void createSkyAndSea();
};