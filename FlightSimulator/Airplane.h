#pragma once
#include "FlightSim.h"

class Airplane
{
public:

	GLfloat part0to3[432 + 6 + 253 + 10][30];
	GLfloat part4to5[19 + 137][30];
	GLfloat part6[186][30];
	GLfloat part7[175][30];
	GLfloat part8to10[9 + 10 + 33][30];
	GLfloat part11[3][30];
	GLfloat part12to13[2 + 5][30];
	GLfloat part14to25[14 + 33 + 27 + 63 + 14 + 106 + 27 + 5 + 162 + 453 + 693 + 20][30];
	GLfloat part26to32[18 + 52 + 328 + 36 + 91 + 56 + 162][30];
	GLfloat proface0[120][30];
	GLfloat proface1[12][30];

	// Arrays for the propeller
	GLfloat provertex[6763][3];
	GLfloat pronormal[6763][3];

	// Arrays for the plane
	GLfloat vertex[6763][3];
	GLfloat normal[6763][3];

public:
	void loadBody();
	void loadPropeller();
	void drawBody();
	void drawPropeller();
	void render(GLfloat theta[]);
};