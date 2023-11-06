/*Libreria usada solo en Windows - debe ir antes que las demás librerias*/
#include<windows.h>
#include<iostream>
/*Libreria del OpenGL*/
#include<GL/glut.h>
using namespace std;
GLfloat x = 10; GLfloat y = 10;
void plano() {
	glColor3f(1, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(-x, 0);
	glVertex2f(x, 0);

	glVertex2f(0, -y);
	glVertex2f(0, y);
	glEnd();
	glPointSize(5);
	glColor3f(0, 0, 1);
	for (GLfloat i = -x+1; i < x ; i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(i, 0);
		glVertex2f(0, i);

	}
	glEnd();
}


void draw(void) {
	plano();
	glFlush();
}




int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Inicializa la librería GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Configura el modo de visualización de la ventana
	glutInitWindowSize(600, 600); // Configura el tamaño de la ventana
	glutInitWindowPosition(300, 100); // Configura la posición de la ventana en la pantalla
	glutCreateWindow("Vaca Gabriel"); // Crea la nueva ventana 	
	gluOrtho2D(-x, x, -y, y); // Configura el plano de trabajo
	glClearColor(0, 0, 0, 0.0); // Configura el color de fondo de la ventana
	glutDisplayFunc(draw); // Asigna y llama la función en donde se dibuja
	glutMainLoop(); // Mantiene en boocle el programa
}
