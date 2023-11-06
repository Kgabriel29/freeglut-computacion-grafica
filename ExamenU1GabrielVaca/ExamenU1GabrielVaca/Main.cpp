#include<GL/glut.h>
#include<Windows.h>
#include<math.h>
#include<iostream>

using namespace std;
GLfloat vertices[3][2] = { {0.0f,0.0f},
						   {1.0f,0.0f},
						   {0.5f,1.0f} };
void plano() {
	//rejilla
	glLineWidth(2);
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_LINES);
	for (GLfloat i = -1; i <= 1; i += 0.1)
	{
		glVertex2f(i, -1);
		glVertex2f(i, 1);
		glVertex2f(-1, i);
		glVertex2f(1, i);
	}
	//glutPostRedisplay();
	glEnd();
	//lineas del palno
	glColor3f(1, 0, 0);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();
	//puntos
	glColor3f(0.1f, 0.0f, 1.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (GLfloat i = -1; i <= 1; i += 0.1)
	{
		glVertex2f(i, 0);
		glVertex2f(0, i);

	}
	glEnd();
	glFlush();
}
void Triangulo() {
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(vertices[2][0], vertices[2][1]);
	glVertex2f(vertices[0][0], vertices[0][1]);
	glVertex2f(vertices[1][0], vertices[1][1]);
	glEnd();
}
void Lineas(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat translate) {
	GLfloat xr1, yr1, xr2,yr2; // son las coordenadas resultantes para mi nueva línea
	xr1 = x1 + translate;
	yr1 = y1 + translate;
	xr2 = x2 + translate;
	yr2 = y2 + translate;
	glLineWidth(4);
	glColor3f(0, 0, 1);
    glBegin(GL_LINES);
	// Linea origunal
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	//linea trasladada
		glColor3f(0, 1, 0);
		glVertex2f(xr1, yr1);
		glVertex2f(xr2, yr2);

    glEnd();
}
void Area() {
	//punto medio
	GLfloat xmedio, ymedio, altura, base, area;
	//diastancia entre 2 puntos final - inicial de los puntos de la base para econtrar la altura
	xmedio = (vertices[1][0] - vertices[0][0]) / 2;
	ymedio = (vertices[1][1] - vertices[0][1]) / 2;
	cout << "El punto para calcula la altura es: (" << xmedio << "," << ymedio << ")" << endl;
	//calculo de la base
	base = sqrt((vertices[1][0] - vertices[0][0]) + (vertices[1][1] - vertices[0][1]));
	cout << "La base del triangulo es: " << base << endl;
	//cálculo de la altura del triángulo
	altura = sqrt((vertices[2][0] - xmedio) + (vertices[2][1] - ymedio));
	cout << "La altura del triangulo es: " << altura << endl;
    //cálculo del área
	area = (base * altura) / 2;
	cout << "El area del triangulo es: " << area <<" cm^2";
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	plano();
	//envia (x1,y1) y (x2,y2) para formar el vector original
	// el último parametro es cuanto se desea trasladar 
	Lineas(-0.2, 0.3, -0.5, 0.3, -0.3);
	Triangulo();
	glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Proyecto Geogebra - Grupo 2");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(draw);
	//Calcula el área
	Area();
    glutMainLoop();
}