// 2-basic2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"

void disPlay(){
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glScalef(2.5/4.0, 2.5/3.0, 2.5);

	// Teapot
	float alpha = 0.1, beta = 0.04;
	for (float i=0; i<70; i+=0.3){
		// float x=i, y=-sin(3*i), theta=-45*(i+3);
		float x=(alpha+beta*i)*cos(i), y=(alpha+beta*i)*sin(i), theta=-45*(i+3);

		float red = i/20, green = (i+6)/20, blue = (i+12)/20;
		if (green>1) green=2-green;
		if (blue>1) blue=2-blue;
		glColor4f(red, green, blue, 0);

		glTranslatef(x, y, 0);
		glRotatef(theta, -1, 1, 0);
		glutWireTeapot(0.08);
		glRotatef(-theta, -1, 1, 0);
		glTranslatef(-x, -y, 0);
	}

	glFlush();
}

void main(void)   
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300,0);
	  
	glutCreateWindow("Lab2-2");
	  
	glutDisplayFunc(disPlay);
	glutMainLoop();   
} 

