#include "Mountain.h"

void Mountain::generateGeo()
{
	int level;
	int idown = 0; // 0 = count up, 1 = count down
	int jdown = 0; // 0 = count up, 1 = count down
	float random; // holds the random number
	for (int i = 0; i < FlightSim::GRIDSIZE + 1; ++i) {
		// random = randomNumber(0.5) - 0.25;
		// count up the mountain
		if (idown == 0)
			level = i;
		// count down the mountain
		if (idown == 1)
			level--;
		// switch to count down the mountain
		if (level == (FlightSim::GRIDSIZE + 1) / 2)
			idown = 1;
		// currentlevel starts the mountain count at 0 inside the j loop
		int currentlevel = -1;
		// initalize jdown to count up the mountain
		int jdown = 0;
		for (int j = 0; j < FlightSim::GRIDSIZE + 1; j++) {
			random = randomNumber(0.5) - 0.25;
			//level division, divide by 2 at each level
			float leveldivision = 1 / (pow(2, currentlevel));
			int insidelevel = currentlevel;
			// start counting down the mountain
			if (currentlevel == ((FlightSim::GRIDSIZE + 1) - j) && jdown == 0)
				jdown = 1;
			// increase mountain height
			if (currentlevel < level && jdown == 0)
				currentlevel++;
			// decrease the mountain height
			if (jdown == 1)
				currentlevel--;
			float leveldvision = (leveldivision) / (1 / (pow(2, insidelevel)));
			grid[i][j].x = i;
			grid[i][j].z = j;
			if (currentlevel != 0)
				// sets the y at a random height
				grid[i][j].y = ((currentlevel*0.25) + random)*leveldvision;
			else
				// sets the y at the ground (0) if the level is 0
				grid[i][j].y = (currentlevel*0.25);
		}
	}
}

void Mountain::calNorms()
{
	int flagx, flagy, flagz;

	// initalize array to -999 so we can check if the spot is filled with a normal value
	for (int i = 0; i < FlightSim::GRIDSIZE + 1; ++i) {
		for (int j = 0; j < FlightSim::GRIDSIZE + 1; ++j) {
			for (int k = 0; k < 4; ++k) {
				norms[i][j][k].x = -999;
				norms[i][j][k].y = -999;
				norms[i][j][k].z = -999;
			}
		}
	}

	for (int i = 0; i < FlightSim::GRIDSIZE; i++) {
		for (int j = 0; j < FlightSim::GRIDSIZE; j++) {
			// get the cross product of current quad in iteration
			v3d tempVec = cross(grid[i][j], grid[i][j + 1], grid[i + 1][j + 1], grid[i + 1][j], 0);

			// reset the storage values (used to check if a spot is filled with a normal)
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// store normal in a spot that doesn't have a normal already
			while (norms[i][j][flagx].x != -999)
				flagx++;
			while (norms[i][j][flagy].y != -999)
				flagy++;
			while (norms[i][j][flagz].z != -999)
				flagz++;

			// store normal in an empty spot
			norms[i][j][flagx].x = tempVec.x;
			norms[i][j][flagy].y = tempVec.y;
			norms[i][j][flagz].z = tempVec.z;

			// get the cross product of current quad in iteration
			tempVec = cross(grid[i][j], grid[i][j + 1], grid[i + 1][j + 1], grid[i + 1][j], 1);

			// reset the storage values (used to check if a spot is filled with a normal)
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// store normal in a spot that doesn't have a normal already
			while (norms[i][j + 1][flagx].x != -999)
				flagx++;
			while (norms[i][j + 1][flagy].y != -999)
				flagy++;
			while (norms[i][j + 1][flagz].z != -999)
				flagz++;

			// store normal in an empty spot
			norms[i][j + 1][flagx].x = tempVec.x;
			norms[i][j + 1][flagy].y = tempVec.y;
			norms[i][j + 1][flagz].z = tempVec.z;

			// store normal in an empty spot
			tempVec = cross(grid[i][j], grid[i][j + 1], grid[i + 1][j + 1], grid[i + 1][j], 2);

			// reset the storage values (used to check if a spot is filled with a normal)
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// store normal in a spot that doesn't have a normal already
			while (norms[i + 1][j + 1][flagx].x != -999)
				flagx++;
			while (norms[i + 1][j + 1][flagy].y != -999)
				flagy++;
			while (norms[i + 1][j + 1][flagz].z != -999)
				flagz++;

			// store normal in an empty spot
			norms[i + 1][j + 1][flagx].x = tempVec.x;
			norms[i + 1][j + 1][flagy].y = tempVec.y;
			norms[i + 1][j + 1][flagz].z = tempVec.z;


			// store normal in an empty spot
			tempVec = cross(grid[i][j], grid[i][j + 1], grid[i + 1][j + 1], grid[i + 1][j], 3);

			// reset the storage values (used to check if a spot is filled with a normal)
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// store normal in a spot that doesn't have a normal already
			while (norms[i + 1][j][flagx].x != -999)
				flagx++;
			while (norms[i + 1][j][flagy].y != -999)
				flagy++;
			while (norms[i + 1][j][flagz].z != -999)
				flagz++;

			// store normal in an empty spot
			norms[i + 1][j][flagx].x = tempVec.x;
			norms[i + 1][j][flagy].y = tempVec.y;
			norms[i + 1][j][flagz].z = tempVec.z;
		}
	}
}

void Mountain::calAvgNorms()
{
	int flagx, flagy, flagz;

	// calculate average normals for smooth shading
	for (int i = 0; i < FlightSim::GRIDSIZE; ++i) {
		for (int j = 0; j < FlightSim::GRIDSIZE; ++j) {

			flagx = 0;
			flagy = 0;
			flagz = 0;

			// check how many normals are at current vertex
			while (norms[i][j][flagx].x != -999 && flagx != 4)
				flagx++;
			while (norms[i][j][flagy].y != -999 && flagy != 4)
				flagy++;
			while (norms[i][j][flagz].z != -999 && flagz != 4)
				flagz++;

			// get all the normals at a given vertex then average them and store in avgNorms
			for (int k = 0; k < flagx; ++k)
				avgNorms[i][j].x = avgNorms[i][j].x + norms[i][j][k].x;
			for (int k = 0; k < flagy; ++k)
				avgNorms[i][j].y = avgNorms[i][j].y + norms[i][j][k].y;
			for (int k = 0; k < flagz; ++k)
				avgNorms[i][j].z = avgNorms[i][j].z + norms[i][j][k].z;

			avgNorms[i][j].x = (avgNorms[i][j].x) / (flagx);
			avgNorms[i][j].y = (avgNorms[i][j].y) / (flagy);
			avgNorms[i][j].z = (avgNorms[i][j].z) / (flagz);

			// quad2 average normal
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// check how many normals are at current vertex
			while (norms[i][j + 1][flagx].x != -999 && flagx != 4)
				flagx++;
			while (norms[i][j + 1][flagy].y != -999 && flagy != 4)
				flagy++;
			while (norms[i][j + 1][flagz].z != -999 && flagz != 4)
				flagz++;

			// get all the normals at a given vertex then average them and store in avgNorms
			for (int k = 0; k < flagx; ++k)
				avgNorms[i][j + 1].x = avgNorms[i][j + 1].x + norms[i][j + 1][k].x;
			for (int k = 0; k < flagy; ++k)
				avgNorms[i][j + 1].y = avgNorms[i][j + 1].y + norms[i][j + 1][k].y;
			for (int k = 0; k < flagz; ++k)
				avgNorms[i][j + 1].z = avgNorms[i][j + 1].z + norms[i][j + 1][k].z;

			avgNorms[i][j + 1].x = (avgNorms[i][j + 1].x) / (flagx);
			avgNorms[i][j + 1].y = (avgNorms[i][j + 1].y) / (flagy);
			avgNorms[i][j + 1].z = (avgNorms[i][j + 1].z) / (flagz);

			// quad4 average normals
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// check how many normals are at current vertex
			while (norms[i + 1][j + 1][flagx].x != -999 && flagx != 4)
				flagx++;
			while (norms[i + 1][j + 1][flagy].y != -999 && flagy != 4)
				flagy++;
			while (norms[i + 1][j + 1][flagz].z != -999 && flagz != 4)
				flagz++;

			// get all the normals at a given vertex then average them and store in avgNorms
			for (int k = 0; k < flagx; ++k)
				avgNorms[i + 1][j + 1].x = avgNorms[i + 1][j + 1].x + norms[i + 1][j + 1][k].x;
			for (int k = 0; k < flagy; ++k)
				avgNorms[i + 1][j + 1].y = avgNorms[i + 1][j + 1].y + norms[i + 1][j + 1][k].y;
			for (int k = 0; k < flagz; ++k)
				avgNorms[i + 1][j + 1].z = avgNorms[i + 1][j + 1].z + norms[i + 1][j + 1][k].z;

			avgNorms[i + 1][j + 1].x = (avgNorms[i + 1][j + 1].x) / (flagx);
			avgNorms[i + 1][j + 1].y = (avgNorms[i + 1][j + 1].y) / (flagy);
			avgNorms[i + 1][j + 1].z = (avgNorms[i + 1][j + 1].z) / (flagz);

			// quad4 average normals
			flagx = 0;
			flagy = 0;
			flagz = 0;

			// check how many normals are at current vertex
			while (norms[i + 1][j][flagx].x != -999 && flagx != 4)
				flagx++;
			while (norms[i + 1][j][flagy].y != -999 && flagy != 4)
				flagy++;
			while (norms[i + 1][j][flagz].z != -999 && flagz != 4)
				flagz++;

			// get all the normals at a given vertex then average them and store in avgNorms
			for (int k = 0; k < flagx; ++k)
				avgNorms[i + 1][j].x = avgNorms[i + 1][j].x + norms[i + 1][j][k].x;
			for (int k = 0; k < flagy; ++k)
				avgNorms[i + 1][j].y = avgNorms[i + 1][j].y + norms[i + 1][j][k].y;
			for (int k = 0; k < flagz; ++k)
				avgNorms[i + 1][j].z = avgNorms[i + 1][j].z + norms[i + 1][j][k].z;

			avgNorms[i + 1][j].x = (avgNorms[i + 1][j].x) / (flagx);
			avgNorms[i + 1][j].y = (avgNorms[i + 1][j].y) / (flagy);
			avgNorms[i + 1][j].z = (avgNorms[i + 1][j].z) / (flagz);

		}
	}
}

void Mountain::drawGeo()
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	int i, j;

	float gridsize = FlightSim::GRIDSIZE;

	// get the highest point of the mountain to make the tops as a function of Y
	GLfloat highestpoint = grid[FlightSim::GRIDSIZE / 2][FlightSim::GRIDSIZE / 2].y;
	GLfloat whiteCapRange = highestpoint - 1.5;
	GLfloat midRange = highestpoint / 2;

	// for every quad in the mesh, draw the quad
	for (i = 0; i < gridsize; i++) {
		for (j = 0; j < gridsize; j++) {

			// Color the top of the mountains white, bottom green if textures = off
			if (!drawTex) {
				if (grid[i][j].y > whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else if (grid[i][j].y > midRange && grid[i][j].y < whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
			}
			// Turn off green & white color if mountain texture = on
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
				glMaterialf(GL_FRONT, GL_SHININESS, 25);
			}

			// Draw normal and vertex of specified quad in mountain mesh
			glNormal3f(avgNorms[i][j].x, avgNorms[i][j].y, avgNorms[i][j].z);
			glTexCoord2f(0 / gridsize + i / gridsize, 0 / gridsize + j / gridsize);
			glVertex3f(grid[i][j].x, grid[i][j].y, grid[i][j].z);

			// Color the top of the mountains white, bottom green if textures = off
			if (!drawTex) {
				if (grid[i][j].y > whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else if (grid[i][j].y > midRange && grid[i][j].y < whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
			}
			// Turn off green & white color if mountain texture = on
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
				glMaterialf(GL_FRONT, GL_SHININESS, 25);
			}

			// Draw normal and vertex of specified quad in mountain mesh
			glNormal3f(avgNorms[i][j + 1].x, avgNorms[i][j + 1].y, avgNorms[i][j + 1].z);
			glTexCoord2f(0 / gridsize + (i) / gridsize, 1 / gridsize + (j + 1) / gridsize);
			glVertex3f(grid[i][j + 1].x, grid[i][j + 1].y, grid[i][j + 1].z);

			// Color the top of the mountains white, bottom green if textures = off
			if (!drawTex) {
				if (grid[i][j].y > whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else if (grid[i][j].y > midRange && grid[i][j].y < whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
			}
			// Turn off green & white color if mountain texture = on
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
				glMaterialf(GL_FRONT, GL_SHININESS, 25);
			}

			// Draw normal and vertex of specified quad in mountain mesh
			glNormal3f(avgNorms[i + 1][j + 1].x, avgNorms[i + 1][j + 1].y, avgNorms[i + 1][j + 1].z);
			glTexCoord2f(1 / gridsize + (i + 1) / gridsize, 1 / gridsize + (j + 1) / gridsize);
			glVertex3f(grid[i + 1][j + 1].x, grid[i + 1][j + 1].y, grid[i + 1][j + 1].z);

			// Color the top of the mountains white, bottom green if textures = off
			if (!drawTex) {
				if (grid[i][j].y > whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else if (grid[i][j].y > midRange && grid[i][j].y < whiteCapRange) {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::green);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
				else {
					glShadeModel(GL_SMOOTH);
					glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::darkGreen);
					glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
					glMaterialf(GL_FRONT, GL_SHININESS, 25);
				}
			}
			// Turn off green & white color if mountain texture = on
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, FlightSim::pureGeo);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, FlightSim::white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, FlightSim::white);
				glMaterialf(GL_FRONT, GL_SHININESS, 25);
			}
			// Draw normal and vertex of specified quad in mountain mesh
			glNormal3f(avgNorms[i + 1][j].x, avgNorms[i + 1][j].y, avgNorms[i + 1][j].z);
			glTexCoord2f(1 / gridsize + (i + 1) / gridsize, 0 / gridsize + j / gridsize);
			glVertex3f(grid[i + 1][j].x, grid[i + 1][j].y, grid[i + 1][j].z);
		}
	}
	glEnd();
}

void Mountain::render()
{
	if (drawTex)
	{
		glEnable(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, FlightSim::mountainTexID);
	drawGeo();
	glDisable(GL_TEXTURE_2D);
}