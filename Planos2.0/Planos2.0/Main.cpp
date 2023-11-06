#include<Windows.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<iostream>
using namespace std;

struct Vector
{
	float x;
	float y;
};Vector vector1;Vector vector2;

void ingreso() {
	cout << "Ingrese el valor en x del primer vector: ";
	cin >> vector1.x;
	cout << "Ingrese el valor en x del primer vector: ";
	cin >> vector1.y;
	cout << "Ingrese el valor en x del segundo vector: ";
	cin >> vector2.x;
	cout << "Ingrese el valor en x del segundo vector: ";
	cin >> vector2.y;
	//glutPostRedisplay(); 
}

void cálculos() {

}

void plano(GLint posX, GLint posY) {

	//dibuja la rejilla
	glLineWidth(2);
	glBegin(GL_LINES);
	for (GLfloat i = -7.0f; i <= 7.0; i += 1.0f) {
		glColor3f(0.4, 0.4, 0.4);
		glVertex2f(i, -7);
		glVertex2f(i, 7);
		glVertex2f(-7, i);
		glVertex2f(7, i);
	}
	glEnd();
	//dibuja los ejes coordenados
	glColor3f(1, 0, 0);
	glLineWidth(6);
	glBegin(GL_LINES);
		glVertex2f(-posX, 0);
		glVertex2f(posX, 0);
		glVertex2f(0, -posY);
		glVertex2f(0, posY);
	glEnd();
	//dibuja los puntos
	
	glPointSize(6);
	glBegin(GL_POINTS);
	for (GLfloat i = -7.0f; i <= 7.0; i += 1.0f) {
		glColor3f(0, 0, 1);
		glVertex2f(i, 0);
		glVertex2f(0, i);
	}
	glEnd();
	
}

void dibujar() {
	glClear(GL_COLOR_BUFFER_BIT);
	plano(7, 7);	 
	
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ventana Gabo");
	
	glClearColor(0.0, 0.0, 0.0, 0);
	gluOrtho2D(-7, 7, -7, 7);
	ingreso();
	glutDisplayFunc(dibujar);
	glutMainLoop();
	return 0;
}