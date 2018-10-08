#include "Airplane.h"

void Airplane::loadBody()
{
	FILE *fp;
	char buff[256];
	int vCount = 0;
	int nCount = 0;
	int subObjCount = -1; // This is so the subObjCount starts at 0 when reading into array
	int fCount = 0;
	GLfloat n = 0;
	int offset, i = 0, j;

	fp = fopen("cessna.txt", "r");

	if (fp == NULL)
		printf("Can't open file");
	else {
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			char *data = buff + 2; // start data pointer where the numbers start
			if (buff[0] == 'v') {
				sscanf(buff, "v %f %f %f", &vertex[vCount][0], &vertex[vCount][1], &vertex[vCount][2]);
				vCount++;

			}
			else if (buff[0] == 'n') {
				sscanf(buff, "n %f %f %f", &normal[nCount][0], &normal[nCount][1], &normal[nCount][2]);
				nCount++;
			}
			else if (buff[0] == 'g') {
				subObjCount++;
				// reset indexing for row array parsing
				if (subObjCount == 4) i = 0;
				if (subObjCount == 6) i = 0;
				if (subObjCount == 7) i = 0;
				if (subObjCount == 8) i = 0;
				if (subObjCount == 11) i = 0;
				if (subObjCount == 12) i = 0;
				if (subObjCount == 14) i = 0;
				if (subObjCount == 26) i = 0;
				if (subObjCount == 33) i = 0;
			}
			else if (buff[0] == 'f' && subObjCount <= 3) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part0to3[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount >= 4 && subObjCount <= 5) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part4to5[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount == 6) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part6[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount == 7) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part7[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount >= 8 && subObjCount <= 10) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part8to10[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount == 11) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part11[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount >= 12 && subObjCount <= 13) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part12to13[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount >= 14 && subObjCount <= 25) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part14to25[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount >= 26 && subObjCount <= 32) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					part26to32[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
		}
	}
	fclose(fp);
}

void Airplane::loadPropeller()
{
	FILE *fp;
	char buff[256];
	int vCount = 0;
	int nCount = 0;
	int subObjCount = -1; // This is so the subObjCount starts at 0 when reading into array
	int fCount = 0;
	GLfloat n = 0;
	int offset, i = 0, j;

	fp = fopen("propeller.txt", "r");

	if (fp == NULL)
		printf("Can't open file");
	else {
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			char *data = buff + 2; // start data pointer where the numbers start
			if (buff[0] == 'v') {
				sscanf(buff, "v %f %f %f", &provertex[vCount][0], &provertex[vCount][1], &provertex[vCount][2]);
				vCount++;

			}
			else if (buff[0] == 'n') {
				sscanf(buff, "f %f %f %f", &pronormal[nCount][0], &pronormal[nCount][1], &pronormal[nCount][2]);
				nCount++;
			}
			else if (buff[0] == 'g') {
				subObjCount++;
				// reset indexing for row array parsing
				if (subObjCount == 1) i = 0;
			}
			else if (buff[0] == 'f' && subObjCount == 0) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					proface0[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
			else if (buff[0] == 'f' && subObjCount == 1) {
				j = 0; // reset indexing for column array parsing
				while (1 == sscanf(data, " %f%n", &n, &offset)) {
					data += offset;
					proface1[i][j] = n;
					j++; // increase column
				}
				i++; // increase row
			}
		}
	}
	fclose(fp);
}

void Airplane::drawBody()
{
	int i = 0;
	int j = 0;
	int pos = 0;

	//yellow subsection of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	for (i = 0; i < 432 + 6 + 253 + 10; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part0to3[i][j] > 0; j++) {
			pos = part0to3[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//blue subsection of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 19 + 137; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part4to5[i][j] > 0; j++) {
			pos = part4to5[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//light purple sub section of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::lightPurple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 186; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part6[i][j] > 0; j++) {
			pos = part6[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//blue subsection of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 175; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part7[i][j] > 0; j++) {
			pos = part7[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//yellow subsection of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 9 + 10 + 33; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part8to10[i][j] > 0; j++) {
			pos = part8to10[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//blue blue subsection of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 3; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part11[i][j] > 0; j++) {
			pos = part11[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//yellow sub section of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 2 + 5; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part12to13[i][j] > 0; j++) {
			pos = part12to13[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//blue sub section of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 14 + 33 + 27 + 63 + 14 + 106 + 27 + 5 + 162 + 453 + 693 + 20; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part14to25[i][j] > 0; j++) {
			pos = part14to25[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	//yellow sub section of plane
	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	for (i = 0; i < 18 + 52 + 328 + 36 + 91 + 56 + 162; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; part26to32[i][j] > 0; j++) {
			pos = part26to32[i][j] - 1;
			glNormal3f(normal[pos][0], normal[pos][1], normal[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}
}

void Airplane::drawPropeller()
{
	int i = 0;
	int j = 0;
	int pos = 0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	// draw first propeller subsection
	for (i = 0; i < 120; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; proface0[i][j] > 0; j++) {
			pos = proface0[i][j] - 1;
			glNormal3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}

	// draw second propeller subsection
	for (i = 0; i < 12; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.75, 0.75, 0.75);
		for (j = 0; proface1[i][j] > 0; j++) {
			pos = proface1[i][j] - 1;
			glNormal3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
			glVertex3f(vertex[pos][0], vertex[pos][1], vertex[pos][2]);
		}
		glEnd();
	}
}

void Airplane::render(GLfloat theta[])
{
	// render airplane
	drawBody();

	// Draw the left propeller
	glPushMatrix();
	glTranslatef(-2.105031, -0.174200, 0.3499989);
	glRotatef(theta[2] * 20, 1.0, 0.0, 0.0);
	glTranslatef(2.105031, 0.174200, -0.3499989);
	drawPropeller();
	glPopMatrix();

	// Draw the right propeller
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.72);
	glTranslatef(-2.105031, -0.174200, 0.3499989);
	glRotatef(theta[2] * 20, 1.0, 0.0, 0.0);
	glTranslatef(2.105031, 0.174200, -0.3499989);
	drawPropeller();
	glPopMatrix();
}