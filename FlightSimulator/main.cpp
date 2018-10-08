#define _CRT_SECURE_NO_DEPRECATE

#include <ctime>
#include "FlightSim.h"

#define ESC 27

// The speed the space ship moves at
GLfloat speedCamera = 0.01 * 1;

GLfloat planeSpeed = 0.1 * 1;

GLfloat planeSpeedInterval = 0.001 * 1;

// Adjust propeller speed
GLfloat rotationSpeed = 0.1 * 10;

GLfloat tiltSpeed = 10 * 1;

// angles for titling the plane direction
GLfloat tiltAngle = 0.0;
GLfloat angleRate = 0.0;
GLfloat planeAngle = 0.0;

// toggles for features
bool enableWireFrame = true;
bool enableGrid = true;
bool enableFullscreen = false;
bool enableMountains = false;

// mouse position
float mousex = 0;
float mousey = 0;


/*******************************************************/
/******************************************************/

// The camera movement
GLfloat zMove = 0.0;
GLfloat xMove = 0.0;
GLfloat yMove = 0.0;

// Thetas for axis (x, y, z)
static GLfloat theta[] = { 0.0, 0.0, 0.0 };

// inital plane/camera position
GLfloat xCamera = 0.0;
GLfloat yCamera = 1.5;
GLfloat zCamera = 0.0;

// vector representing inital camera direction
GLfloat xlCamera = 0.0;
GLfloat ylCamera = 0.5;
GLfloat zlCamera = 0.0;

// window dimensions
GLint windowWidth = 600;
GLint windowHeight = 400;


// objects
Background background;
Mountain mountain[3];
Airplane airplane;

/************************************************************************

Function:      mouseMotion

Description:    updates mouse co-ordinates

*************************************************************************/

void mouseMotion(int x, int y) {
	float var = windowWidth / 2;

	// get mouse co-ords for the tilt of the plane
	mousex = ((x - var) / var)*0.5;
	tiltAngle = ((x - var) / var) * 45;

	// inverse rotation to match mouse orientation
	angleRate = mousex*-1;
}


/************************************************************************

Function:		myDisplay

Description:	Display callback, clears frame buffer and depth buffer,
positions the camera and draws the cube.

*************************************************************************/
void display(void)
{

	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix into the model view matrix
	glLoadIdentity();

	glPushMatrix();
	// set the camera position
	gluLookAt(xCamera, yCamera, zCamera,
		xlCamera, ylCamera, zlCamera,
		0, 1, 0);

	// position light 0
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, FlightSim::lightPosition);
	glPopMatrix();

	if (enableGrid)
		// Generate Scene
		background.createScene();
	else {
		// Generate the map
		background.createSkyAndSea();
	}

	if (enableMountains) {
		// Draw the 3 randomly generated mountains
		glPushMatrix();
		glTranslatef(10, 0, 10);
		glScalef(0.4, 0.5, 0.4);
		mountain[0].render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(20, 0, -5);
		glScalef(0.25, 0.5, 0.25);
		mountain[1].render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-25, 0, -20);
		glScalef(0.6, 0.5, 0.6);
		mountain[2].render();
		glPopMatrix();
	}

	if (enableWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPopMatrix();

	glPushMatrix();

	// Draw the plane
	glTranslatef(0.0, -0.5, -2.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);


	glScalef(0.65, 0.65, 0.65);
	/*-------------------------------------------*/
	// render airplane
	airplane.render(theta);
	/*-------------------------------------------*/

	glPopMatrix();

	// swap the drawing buffers
	glutSwapBuffers();

}

/************************************************************************

Function:		myIdle

Description:	Updates the animation when idle.

*************************************************************************/
void idel()
{

	// change plane altitude
	if (yMove) {
		yCamera += yMove*speedCamera;
		ylCamera += yMove*speedCamera;
	}

	// calculate tilt angle of plane with the mouse
	planeAngle += angleRate;
	zCamera += (cos(planeAngle*(FlightSim::rad))*planeSpeed);
	xCamera += (sin(planeAngle*(FlightSim::rad))*planeSpeed);
	xlCamera = xCamera + (sin(planeAngle*(FlightSim::rad))*tiltSpeed);
	zlCamera = zCamera + (cos(planeAngle*(FlightSim::rad))*tiltSpeed);

	// rotation speed of propeller
	theta[2] += (0.1*rotationSpeed);
	if (theta[2] >= 360.0)
		theta[2] -= (360.0*rotationSpeed);

	// Redraw the new state
	glutPostRedisplay();
}

/************************************************************************

Function:		normalKey, pressKey, releaseKey

Description:	User input callbacks

*************************************************************************/
void keyboard(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q')
		exit(0);

	// enable wireframe if w pressed
	if (key == 'w' || key == 'W')
		enableWireFrame = !enableWireFrame;

	// enable the scene if s is pressed
	if (key == 's' || key == 'S')
		enableGrid = !enableGrid;

	// enable fog if b is pressed
	if (key == 'b' || key == 'B')
		background.switchEnableFogTag();

	// enable mountains if m is pressed
	if (key == 'm' || key == 'M') 
		enableMountains = !enableMountains;

	// enable mountain textures if t is pressed
	if (key == 't' || key == 'T')
	{
		for (int i = 0; i < 3; ++i)
		{
			mountain[i].switchDrawTexTag();
		}
	}

	// enable fullscreen if f is pressed
	if (key == 'f' || key == 'F') 
	{
		enableFullscreen = !enableFullscreen;
		if (enableFullscreen)
		{
			glutFullScreen();
		}
		else
		{
			glutPositionWindow(100, 100);
			glutReshapeWindow(windowWidth, windowHeight);
		}

	}

}

// handles speeding up plane and changing plane altitude with PAGE UP/DOWN and UP/DOWN arrow
void pressKey(int key, int xx, int yy)
{
	int i;
	switch (key) {
	case GLUT_KEY_UP: yMove = 1.0; break;
	case GLUT_KEY_DOWN:
		if (ylCamera > 0 || yCamera > 0)
			yMove = -1.0; break;
	case GLUT_KEY_PAGE_UP: planeSpeed += planeSpeedInterval; break;
	case GLUT_KEY_PAGE_DOWN:
		if (planeSpeed > planeSpeedInterval * 25)
			planeSpeed -= planeSpeedInterval; break;
	}
}

void releaseKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: yMove = 0.0; break;
	case GLUT_KEY_DOWN: yMove = 0.0; break;
	case GLUT_KEY_PAGE_UP: planeSpeed += 0.0; break;
	case GLUT_KEY_PAGE_DOWN: planeSpeed += 0.0; break;
	}
}


/************************************************************************

Function:		myResize

Description:	Handles a user resize of the window.

*************************************************************************/
void reshape(int newWidth, int newHeight)
{

	// Update the new width
	windowWidth = newWidth;
	// Update the new height
	windowHeight = newHeight;

	// Update the viewport to still be all of the window
	glViewport(0, 0, windowWidth, windowHeight);

	// Change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// Load the identity matrix into the projection matrix
	glLoadIdentity();

	// gluPerspective(fovy, aspect, near, far)
	gluPerspective(45, (float)windowWidth / (float)windowHeight, 1, 10000);

	// Change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	srand(((unsigned)time(NULL)));
	FlightSim::printControls();
	FlightSim::initialize();
	airplane.loadBody();
	airplane.loadPropeller();
	for (int i = 0; i < 3; ++i)
	{
		mountain[i].generateGeo();
		mountain[i].calNorms();
		mountain[i].calAvgNorms();
	}

	FlightSim::mountainTexID = FlightSim::loadppm("mount03.ppm");
	FlightSim::skyTexID = FlightSim::loadppm("sky08.ppm");
	FlightSim::seaTexID = FlightSim::loadppm("sea02.ppm");

}
/************************************************************************

Function:		main

Description:	Sets up the openGL rendering context and the windowing
system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
		// Set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// Set window size
	glutInitWindowSize(windowWidth, windowHeight);
	// Set window position on screen
	glutInitWindowPosition(100, 150);
	// Open the screen window
	glutCreateWindow("Flight Simulation");


	init();

	glutDisplayFunc(display);
	glutIdleFunc(idel);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutPassiveMotionFunc(mouseMotion);

	// Initialize the rendering context
	
	// Go into a perpetual loop
	glutMainLoop();
}