// 4-half_sphere.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
 
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //光照
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

int width = 300, height = 300;

void display2(void)
{
	GLdouble eqn2[4] = { 1.0, 1.0, 1.0, -2.7 };
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
 
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
 
	glClipPlane(GL_CLIP_PLANE1, eqn2);
	glEnable(GL_CLIP_PLANE1); 
	glRotatef(35.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glutWireSphere(1.0, 60, 64);
	
	glPopMatrix();
	glFlush();
 
}

 
void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
	glShadeModel(GL_SMOOTH);
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void main(void) {
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 0);
	  
	glutCreateWindow("Lab2-4");
	  
	init();
	glutDisplayFunc(display2);

	glutMainLoop();   
} 

