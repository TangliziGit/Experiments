// 1-basic.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"

void disPlay(){
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// sphere
	glColor4f(0.5, 0, 0, 0);
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(35, 0, 1, 0);
	glutWireSphere(0.3, 12, 12);
	glRotatef(-35, 0, 1, 0);
	glTranslatef(0.5, -0.5, 0);

	// cone
	glColor4f(0.5, 0.5, 0, 0);
	glTranslatef(0.3, 0.5, 0);
	glRotatef(75, 0.5, 1, 0);
	glutWireCone(0.3, 0.5, 10, 10);
	glRotatef(-75, 0.5, 1, 0);
	glTranslatef(-0.3, -0.5, 0);

	// Teapot
	glColor4f(0, 0.5, 0.5, 0);
	glTranslatef(-0.5, -0.5, 0);
	glRotatef(-45, -1, 1, 0);
	glutWireTeapot(0.35);
	glRotatef(45, -1, 1, 0);
	glTranslatef(0.5, 0.5, 0);

	// 6 face
	glColor4f(0.5, 0, 0.5, 0);
	glTranslatef(0.5, -0.5, 0);
	glRotatef(-75, 1.6, 1, 0);
	glutWireCube(0.4);
	glRotatef(75, 1.6, 1, 0);
	glTranslatef(-0.5, 0.5, 0);

	glFlush();
}

void main(void)   
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(300,0);
	  
	glutCreateWindow("Lab2-1");
	  
	glutDisplayFunc(disPlay);
	glutMainLoop();   
} 

