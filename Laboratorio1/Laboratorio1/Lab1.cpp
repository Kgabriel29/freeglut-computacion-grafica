/*Libreria usada solo en Windows - debe ir antes que las demás librerias*/
#include<windows.h>
#include<iostream>
/*Libreria del OpenGL*/
#include<GL/glut.h>
using namespace std;
void cuadrado(GLfloat v) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	// Coordenadas de los vértices del cuadrado
	glVertex2f(-v, v);
	glVertex2f(-v, -v);
	glVertex2f(v, -v);
	glVertex2f(v, v);
	glEnd();
	
}
void triangulo(GLfloat v) {
	glBegin(GL_TRIANGLES); // Inicia el dibujo de triángulos

	for (GLfloat i = 1.0f; i < v; i+=0.2)
	{
		// se crea 3 varibles con números randímicos entre el 1 y 10
		GLfloat randomR = rand() % 10, randomG = rand() % 10, randomB = rand() % 10;
		//se divide estos números para 10 teniendo en cuenta que los valores aceptados van entre 1 y 0
		glColor3f(randomR / 10.0f, randomG / 10.0f, randomB / 10.0f);

		// Coordenadas de los vértices del triángulo equilátero
		glVertex2f(-v + i, -v + i);
		glVertex2f(0.0f, v - i);
		glVertex2f(v - i, -v + i);
	}
	glEnd();
}

void draw(void)// esta función siempre tiene que tener como parámetro void
{
	glClear(GL_COLOR_BUFFER_BIT); // Limpia la ventana y asigna el color establecido

	GLfloat posCua = 6.5f; // Variable usada para la generación del cuadrado y triángulo

	cuadrado(posCua);
	triangulo(posCua);
	glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Inicializa la librería GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Configura el modo de visualización de la ventana
	glutInitWindowSize(600, 600); // Configura el tamaño de la ventana
	glutInitWindowPosition(300, 100); // Configura la posición de la ventana en la pantalla
	glutCreateWindow("Vaca Gabriel"); // Crea la nueva ventana 	
	gluOrtho2D(-10, 10, -10, 10); // Configura el plano de trabajo
	glClearColor(0, 0, 0, 0.0); // Configura el color de fondo de la ventana
	glutDisplayFunc(draw); // Asigna y llama la función en donde se dibuja
	glutMainLoop(); // Mantiene en boocle el programa
}
