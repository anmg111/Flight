#pragma once

#include "Point3d.h"
#include "FlightSim.h"

using v3d = Point3d;

class Mountain
{
public:
	v3d grid[FlightSim::GRIDSIZE + 1][FlightSim::GRIDSIZE + 1];
	v3d norms[FlightSim::GRIDSIZE + 1][FlightSim::GRIDSIZE + 1][4];
	v3d avgNorms[FlightSim::GRIDSIZE + 1][FlightSim::GRIDSIZE + 1];
	bool drawTex;

public:
	Mountain()
	{
		drawTex = false;
	}

	inline void switchDrawTexTag()
	{
		drawTex = !drawTex;
	}

	void generateGeo();
	void calNorms();
	void calAvgNorms();
	void drawGeo();
	void render();

private:
	inline float randomNumber(float max) {
		float x = ((float)std::rand() / (float)(RAND_MAX)) * max;
		return x;
	}
};