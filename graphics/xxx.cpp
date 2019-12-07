// 1-solar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"

GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

float moonArc = 0.0f;
float earthArc = 0.0f;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -300.0f); 

    glDisable(GL_LIGHTING);
	glColor3ub(255, 127, 0);
	glRotatef(180, -0.25f, 1.0f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, -0.25f);
	glutSolidSphere(15.0f, 30, 17);
    glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glRotatef(earthArc, 0.0f, 1.0f, 0.0f);
	glColor3ub(0, 0, 255);
	glTranslatef(100.0f, 0.0f, 0.0f);
	glutSolidSphere(10.0f, 30, 17);

	glColor3ub(200, 200, 200);
	glRotatef(moonArc, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 30, 17);

	glPopMatrix();

	earthArc += 5.0f;
	if(earthArc > 360) earthArc = 0.0f;

	moonArc += 15.0f;
	if(moonArc > 360) moonArc = 0.0f;

	glutSwapBuffers();
}

void setup(){
	glEnable(GL_DEPTH_TEST);
	//逆时针为多边形正面
	glFrontFace(GL_CCW);
	//启用剔除效果，多边形背面不用光照处理
	glEnable(GL_CULL_FACE);  
	glEnable(GL_LIGHTING);

	//环境光颜色
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	//散射光强度
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL);
	//设置材料反射属性， 以相同的强度反射环境光和散射光
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(50.0f, w/(float)h, 1.0, 425.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}


int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	setup();
	glutTimerFunc(250, timer, 1);
	glutMainLoop();
 
	return 0;
}
