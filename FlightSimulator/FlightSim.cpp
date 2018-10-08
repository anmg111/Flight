#include "FlightSim.h"

GLfloat FlightSim::rad = M_PI / 180.0;
GLfloat FlightSim::pureGeo[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat FlightSim::darkGreen[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat FlightSim::lightBlue[4] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat FlightSim::blue[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat FlightSim::yellow[4] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat FlightSim::black[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat FlightSim::lightPurple[4] = { 0.87, 0.58, 0.98, 1.0 };
GLfloat FlightSim::red[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat FlightSim::green[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat FlightSim::white[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat FlightSim::fogColor[3] = {0.737255, 0.560784, 0.560784};
GLfloat FlightSim::lightPosition[4] = { 0.0, 1000.0, 0.0, 0.0 };

GLuint FlightSim::mountainTexID = FlightSim::loadppm("mount03.ppm");
GLuint FlightSim::skyTexID = FlightSim::loadppm("sky08.ppm");
GLuint FlightSim::seaTexID = FlightSim::loadppm("sea02.ppm");
