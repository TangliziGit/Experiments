// 3-OpenGl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"

void disPlay(){
	float color = 0.8;
	glClearColor(color, color, color, 0); 
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Line
	glColor4f(0.5, 0, 0, 0.5);
	glBegin(GL_LINES);
	for (float y=1; y>0.2; y-=0.01){
		glVertex2f(-1, y);
		glVertex2f(-0.1, y);
	}
	glEnd();

	// poly
	glColor4f(0, 0.5, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.2, 0.2);
		glVertex2f(0.8, 0.2);
		glVertex2f(0.3, 0.8);
		glVertex2f(0.2, 0.8);
	glEnd();

	// circle
	float ox=0.5, oy=0.5, rad=0.2;
	glColor4f(0, 0, 0.5, 0);
	glBegin(GL_LINE_LOOP);
	for (float theta=0; theta<2*acos(-1.0); theta+=0.01)
		glVertex2f(rad*cos(theta)+ox, rad*sin(theta)+oy);
	glEnd();

	// cone
	glColor4f(0.5, 0.5, 0, 0);
	glRotatef(75, 0, 1, 0);
	glTranslatef(0.5, -0.5, 0);
	glutWireCone(0.3, 0.5, 10, 10);

	// Teapot
	glColor4f(0, 0.5, 0.5, 0);
	glRotatef(-75, 0, 1, 0);
	glTranslatef(-0.7, 0, 0);
	gluLookAt(0, 0.3, 0.3,
			0, 0, 0,
			0, 1, 0);
	glutWireTeapot(0.2);

	// 6 face
	glColor4f(0.5, 0, 0.5, 0);
	glRotatef(-75, 1.6, 1, 0);
	glTranslatef(0.5, 0.5, 0.2);
	glutWireCube(0.4);


	glFlush();
}

//主函数
void main(void)   
{

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(300,0);
	  
	glutCreateWindow("Hello");   
	  
	glutDisplayFunc(disPlay);
	/*glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);	
	*/
	glutMainLoop();   
} 

