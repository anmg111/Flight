#include "Background.h"

void Background::createScene()
{

	// red line for x frame of reference
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	// green line for y frame of reference
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::green);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	// blue line for blue frame of reference
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glColor3f(0.0, 0.0, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glLineWidth(1.0);

	// white sphere for origin
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glColor3f(1.0, 1.0, 1.0);
	gluSphere(qobj, 0.05, 15, 10);
	gluDeleteQuadric(qobj);

	// center grid of CxC
	float xStart = (-1)*(FlightSim::C / 2);
	float zStart = (-1)*(FlightSim::C / 2);


	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::lightBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	// draw the quad flooring for the basic scene
	glBegin(GL_QUADS);
	int x;
	int z;
	for (x = xStart; x < FlightSim::C / 2; x++) {
		for (z = zStart; z < FlightSim::C / 2; z++) {
			glNormal3d(0, 1, 0);  // normal of the floor is pointing up
			glVertex3f(x, 0, z);
			glVertex3f(x + 1, 0, z);
			glVertex3f(x + 1, 0, z + 1);
			glVertex3f(x, 0, z + 1);
		}
	}
	glEnd();
}

void Background::createSkyAndSea()
{

	GLUquadricObj *qobj;


	// Construct Cylinder walls of the map and texture when enabled
	qobj = gluNewQuadric();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialfv(GL_FRONT, GL_EMISSION, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, FlightSim::skyTexID);
	gluQuadricTexture(qobj, FlightSim::skyTexID);
	glTranslatef(0, -3, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(qobj, FlightSim::C / 2, FlightSim::C / 2, 35, 100, 60);
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT, GL_EMISSION, FlightSim::black);

	glPopMatrix();


	// draw fog on the ocean if enabled
	if (enableFog) {
		glEnable(GL_FOG);
		FlightSim::enableFog();
	}

	// Construct disk floor of the map and texture when enabled
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glRotatef(-90, 1.0, 0.0, 0.0);
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, FlightSim::seaTexID);
	gluQuadricTexture(qobj, FlightSim::seaTexID);
	gluDisk(qobj, 0, FlightSim::C / 2, 100, 100);
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(qobj);
	glPopMatrix();

	// turn off fog after done drawing ocean
	if (enableFog)
		glDisable(GL_FOG);
}