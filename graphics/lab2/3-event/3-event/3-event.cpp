// 3-event.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include <string.h>

#define max(a, b) (((a)>(b))?(a):(b))
#define min(a, b) (((a)<(b))?(a):(b))

float scale = 1, theta = -45;
float ex = 0, ey = 0;
float sx = 4, sy = 3;


void* bitmap_fonts[7] = {
        GLUT_BITMAP_9_BY_15,
        GLUT_BITMAP_8_BY_13,
        GLUT_BITMAP_TIMES_ROMAN_10,
        GLUT_BITMAP_TIMES_ROMAN_24,
        GLUT_BITMAP_HELVETICA_10,
        GLUT_BITMAP_HELVETICA_12,
        GLUT_BITMAP_HELVETICA_18
};
void print_bitmap_string(void* font,const char* s)
{
    if (s && strlen(s)) {
        while (*s) {
            glutBitmapCharacter(font, *s);
            s++;
        }
    }
}
int TextOut(float x,float y,const char* cstr)
{
    glRasterPos2f(x, y);
    print_bitmap_string(bitmap_fonts[5], cstr);
    return 1;
}

void display(void);

int px=0, py=0;
void mouse(int button, int state, int x, int y){
	px=x; py=y;
	display();
}

void keys(unsigned char key, int x, int y){
	display();
}

void motion(int x, int y){
	int dx=x-px, dy=y-py;
	printf("<%d, %d> scale%f, theta%f\n", dx, dy, scale, theta);

	ex+=dx/800.0;
	ey+=dy/600.0;

	px=x; py=y;
	display();
}

void reshape(int wei, int hei){
	sx = wei/100;
	sy = hei/100;

	display();
}

void display(){
	int xx=2;
	
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1/sx, 1/sy, 1);
	glOrtho(-xx, xx, -xx, xx, -xx, xx);

	glColor4f(0.5, 0, 0, 0);
	TextOut(-4, -2, "You can hold on mouse, and move the mouse to change your view point.");

	gluLookAt(ex, ey, 1,
			0, 0, 0,
			0, 1, 0);

	// Teapot
	glColor4f(0, 0.5, 0.5, 0);
	
	// glTranslatef(-0.5, -0.5, 0);
	// glRotatef(45+theta, -1, 1, 0);
	glutWireTeapot(scale);
	// glRotatef(-(45+theta), -1, 1, 0);
	// glTranslatef(0.5, 0.5, 0);

	glScalef(sx, sy, 1);

	glFlush();
}


void main(void)   
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 0);
	
	glutCreateWindow("Lab2-3");
	  
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();   
} 

