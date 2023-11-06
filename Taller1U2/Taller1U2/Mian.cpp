#include<Windows.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<iostream>
using namespace std;

void plano(GLint posX, GLint posY) {
    glLineWidth(2);
    glColor3f(0.7, 0.7, 0.7);

    // Dibujar rejilla
    glBegin(GL_LINES);
    for (GLfloat i = -posX; i <= posX; i += 1.0f) {
        glVertex2f(i, -posY);
        glVertex2f(i, posY);
        glVertex2f(-posX, i);
        glVertex2f(posX, i);
    }
    glEnd();

    // Dibujar ejes coordenados
    glLineWidth(3);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-posX, 0);
    glVertex2f(posX, 0);
    glVertex2f(0, -posY);
    glVertex2f(0, posY);
    glEnd();

    // Dibujar puntos
    glPointSize(6);
    glColor3f(0, 0, 0.4);
    glBegin(GL_POINTS);
    for (GLfloat i = -posX; i <= posX; i += 1.0f) {
        glVertex2f(i, 0);
        glVertex2f(0, i);
    }
    glEnd();
}


void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	plano(10, 10);
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Ventana Gabo");

	glClearColor(1.0, 1.0, 1.0, 0);
	gluOrtho2D(-10, 10, -10, 10);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}