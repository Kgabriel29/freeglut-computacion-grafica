/*Libreria usada solo en Windows - debe ir antes que las dem�s librerias*/
#include<windows.h>
#include<iostream>
/*Libreria del OpenGL*/
#include<GL/glut.h>
using namespace std;
void cuadrado(GLfloat v) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	// Coordenadas de los v�rtices del cuadrado
	glVertex2f(-v, v);
	glVertex2f(-v, -v);
	glVertex2f(v, -v);
	glVertex2f(v, v);
	glEnd();
	
}
void triangulo(GLfloat v) {
	glBegin(GL_TRIANGLES); // Inicia el dibujo de tri�ngulos

	for (GLfloat i = 1.0f; i < v; i+=0.2)
	{
		// se crea 3 varibles con n�meros rand�micos entre el 1 y 10
		GLfloat randomR = rand() % 10, randomG = rand() % 10, randomB = rand() % 10;
		//se divide estos n�meros para 10 teniendo en cuenta que los valores aceptados van entre 1 y 0
		glColor3f(randomR / 10.0f, randomG / 10.0f, randomB / 10.0f);

		// Coordenadas de los v�rtices del tri�ngulo equil�tero
		glVertex2f(-v + i, -v + i);
		glVertex2f(0.0f, v - i);
		glVertex2f(v - i, -v + i);
	}
	glEnd();
}

void draw(void)// esta funci�n siempre tiene que tener como par�metro void
{
	glClear(GL_COLOR_BUFFER_BIT); // Limpia la ventana y asigna el color establecido

	GLfloat posCua = 6.5f; // Variable usada para la generaci�n del cuadrado y tri�ngulo

	cuadrado(posCua);
	triangulo(posCua);
	glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Inicializa la librer�a GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Configura el modo de visualizaci�n de la ventana
	glutInitWindowSize(600, 600); // Configura el tama�o de la ventana
	glutInitWindowPosition(300, 100); // Configura la posici�n de la ventana en la pantalla
	glutCreateWindow("Vaca Gabriel"); // Crea la nueva ventana 	
	gluOrtho2D(-10, 10, -10, 10); // Configura el plano de trabajo
	glClearColor(0, 0, 0, 0.0); // Configura el color de fondo de la ventana
	glutDisplayFunc(draw); // Asigna y llama la funci�n en donde se dibuja
	glutMainLoop(); // Mantiene en boocle el programa
}
