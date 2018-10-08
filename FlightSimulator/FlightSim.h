#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>
#include <cstdio>

class FlightSim {

public:
	static const int C = 100;
	static const int GRIDSIZE = 40;

	static GLfloat rad;

	static GLfloat pureGeo[4];
	static GLfloat darkGreen[4];
	static GLfloat lightBlue[4];
	static GLfloat blue[4];
	static GLfloat yellow[4];
	static GLfloat black[4];
	static GLfloat lightPurple[4];
	static GLfloat red[4];
	static GLfloat green[4];
	static GLfloat white[4];
	static GLfloat fogColor[3];
	static GLfloat lightPosition[4];

	static GLuint mountainTexID;
	static GLuint skyTexID;
	static GLuint seaTexID;



	inline static void enableFog()
	{
		// set fog color and density
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_MODE, GL_EXP);
		glFogf(GL_FOG_DENSITY, 0.1);
	}

	inline static unsigned int loadppm(char filename[])
	{
		GLuint myTextureID;
		GLubyte *imageData;
		int imageWidth;
		int imageHeight;

		// the ID of the image file
		FILE *fileID;

		// maxValue
		int  maxValue;

		// total number of pixels in the image
		int  totalPixels;

		// temporary character
		char tempChar;

		// counter variable for the current pixel in the image
		int i;

		// array for reading in header information
		char headerLine[100];

		float RGBScaling;

		// temporary variables for reading in the red, green and blue data of each pixel
		int red, green, blue;

		// open the image file for reading
		fileID = fopen(filename, "r");

		// read in the first header line
		fscanf(fileID, "%[^\n] ", headerLine);

		// make sure that the image begins with 'P3', which signifies a PPM file
		if ((headerLine[0] != 'P') || (headerLine[1] != '3'))
		{
			// printf("This is not a PPM file!\n"); 
			exit(0);
		}

		// we have a PPM file
		// printf("This is a PPM file\n");

		// read in the first character of the next line
		fscanf(fileID, "%c", &tempChar);

		// while we still have comment lines (which begin with #)
		while (tempChar == '#')
		{
			// read in the comment
			fscanf(fileID, "%[^\n] ", headerLine);

			// print the comment
			// printf("%s\n", headerLine);

			// read in the first character of the next line
			fscanf(fileID, "%c", &tempChar);
		}

		// the last one was not a comment character '#', so we nee dto put it back into the file stream (undo)
		ungetc(tempChar, fileID);

		// read in the image hieght, width and the maximum value
		fscanf(fileID, "%d %d %d", &imageWidth, &imageHeight, &maxValue);

		// print out the information about the image file
		// printf("%d rows  %d columns  max value= %d\n", imageHeight, imageWidth, maxValue);

		// compute the total number of pixels in the image
		totalPixels = imageWidth * imageHeight;

		// allocate enough memory for the image  (3*) because of the RGB data
		imageData = (GLubyte *)malloc(3 * sizeof(GLuint) * totalPixels);


		// determine the scaling for RGB values
		RGBScaling = 255.0 / maxValue;


		// if the maxValue is 255 then we do not need to scale the 
		//    image data values to be in the range or 0 to 255
		if (maxValue == 255)
		{
			for (i = 0; i < totalPixels; i++)
			{
				// read in the current pixel from the file
				fscanf(fileID, "%d %d %d", &red, &green, &blue);

				// store the red, green and blue data of the current pixel in the data array
				imageData[3 * totalPixels - 3 * i - 3] = red;
				imageData[3 * totalPixels - 3 * i - 2] = green;
				imageData[3 * totalPixels - 3 * i - 1] = blue;
			}
		}
		else  // need to scale up the data values
		{
			for (i = 0; i < totalPixels; i++)
			{
				// read in the current pixel from the file
				fscanf(fileID, "%d %d %d", &red, &green, &blue);

				// store the red, green and blue data of the current pixel in the data array
				imageData[3 * totalPixels - 3 * i - 3] = red   * RGBScaling;
				imageData[3 * totalPixels - 3 * i - 2] = green * RGBScaling;
				imageData[3 * totalPixels - 3 * i - 1] = blue  * RGBScaling;
			}
		}


		// close the image file
		fclose(fileID);

		glGenTextures(1, &myTextureID);
		// bind the texture
		glBindTexture(GL_TEXTURE_2D, myTextureID);

		//configuration
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//wrap or cut off based on param
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// build 2d mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight,
			GL_RGB, GL_UNSIGNED_BYTE, imageData);

		free(imageData);

		return myTextureID;
	}

	inline static void initialize()
	{
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		// Set background color to be black
		glClearColor(0, 0, 0, 1.0);

		// define the light color and intensity
		GLfloat ambientLight[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

		//  the global ambient light level
		GLfloat globalAmbientLight[] = { 0.4, 0.4, 0.4, 1.0 };

		// set the global ambient light level
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

		// define the color and intensity for light 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

		// enable lighting 
		glEnable(GL_LIGHTING);

		// enable light 0
		glEnable(GL_LIGHT0);

		// make sure the normals are unit vectors
		glEnable(GL_NORMALIZE);

		glDisable(GL_CULL_FACE);
	}

	inline static void printControls()
	{
		printf("Scene Controls\n");
		printf("----------------\n");
		printf("f:	toggle fullscreen\n");
		printf("b:	toggle fog\n");
		printf("m:	toggle mountains\n");
		printf("t:	toggle mountain texture\n");
		printf("s:	toggle sea & sky\n");
		printf("w:	toggle wireframe\n\n");
		printf("q:	quit\n");

		printf("Camera Controls\n");
		printf("----------------\n");
		printf("Up Arrow:	move up\n");
		printf("Down Arrow:	move down\n");
		printf("PAGE UP:	speed up\n");
		printf("PAGE DOWN:	slow down\n\n");

	}

};

#include "Mountain.h"
#include "Background.h"
#include "Airplane.h"