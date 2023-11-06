#include<Windows.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<iostream>
using namespace std;

GLint x=5; GLint y=5;
void plano(GLint posX, GLint posY) {
	
	glColor3f(1, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(-posX, 0);
	glVertex2f(posX, 0);
	glVertex2f(0, -posY);
	glVertex2f(0, posY);
	glEnd();
}

//cout << "i: " << i << endl;
////cout << "posición:(" << i << ")( 0 )";
//cout << "posición:(" << i << ")(  " << i << ")" << endl;
////cout << "posición:(" << i << ")( 0 )";
//cout << "posición:(" << -i << ")(  " << -i << ")" << endl;
void puntoplano() {
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	for (GLfloat i = -5.0; i <= 5.0; i+= 1.0)
	{
		glVertex2f(i, -5.0);
		glVertex2f(i, 5.0);
		glVertex2f(-5.0, i);
		glVertex2f(5.0, i);
	}
	glutPostRedisplay();
	glEnd();	
}


void dibujar() {
	glClear(GL_COLOR_BUFFER_BIT);
	plano( x , y);
	puntoplano();
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);

	glutCreateWindow("Ventana Gabo");
	glutDisplayFunc(dibujar);
	glutMainLoop();
	return 0;
}