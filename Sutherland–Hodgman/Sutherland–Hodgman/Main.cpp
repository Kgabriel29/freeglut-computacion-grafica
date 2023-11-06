#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <iostream>

using namespace std;

typedef struct {
	float x;
	float y;
}PT;

int n, i, j;
PT p1, p2, p[20], pp[20];

void izquierda() {
	i = 0; j = 0;

	for (i = 0; i < n; i++)
	{
		if (p[i].x < p1.x && p[i + 1].x >= p1.x)
		{
			if (p[i + 1].x - p[i].x != 0)
			{
				pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y;
			}
			else
			{
				pp[j].y = p[i].y;
			}
			pp[j].x = p1.x;
			j++;
			pp[j].x = p[i + 1].x;
			pp[j].y = p[i + 1].y;
			j++;

		}

		if (p[i].x >= p1.x && p[i + 1].x >= p1.x)
		{
			pp[j].y = p[i + 1].y;
			pp[j].x = p[i + 1].x;
			j++;
		}

		if (p[i].x >= p1.x && p[i + 1].x < p1.x)
		{
			if (p[i + 1].x - p[i].x != 0)
			{
				pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p1.x - p[i].x) + p[i].y;
			}
			else
			{
				pp[j].y = p[i].y;
			}
			pp[j].x = p1.x;
			j++;
		}
	}

	for (i = 0; i < j; i++)
	{
		p[i].x = pp[i].x;
		p[i].y = pp[i].y;
	}

	p[i].x = pp[0].x;
	p[i].y = pp[0].y;
	n = j;

}

void derecha() {
	i = 0; j = 0;

	for (i = 0; i < n; i++)
	{
		if (p[i].x > p2.x && p[i + 1].x <= p2.x)
		{
			if (p[i + 1].x - p[i].x != 0)
			{
				pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y;
			}
			else
			{
				pp[j].y = p[i].y;
			}
			pp[j].x = p2.x;
			j++;
			pp[j].x = p[i + 1].x;
			pp[j].y = p[i + 1].y;
			j++;
		}

		if (p[i].x <= p2.x && p[i + 1].x <= p2.x)
		{
			pp[j].y = p[i + 1].y;
			pp[j].x = p[i + 1].x;
			j++;
		}

		if (p[i].x <= p2.x && p[i + 1].x > p2.x)
		{
			if (p[i + 1].x - p[i].x != 0)
			{
				pp[j].y = (p[i + 1].y - p[i].y) / (p[i + 1].x - p[i].x) * (p2.x - p[i].x) + p[i].y;			// only save point of intersection
			}
			else
			{
				pp[j].y = p[i].y;
			}
			pp[j].x = p2.x;
			j++;
		}

	}

	for (i = 0; i < j; i++)
	{
		p[i].x = pp[i].x;
		p[i].y = pp[i].y;
	}

	p[i].x = pp[0].x;
	p[i].y = pp[0].y;

}

void arriba() {
	i = 0; j = 0;

	for (i = 0; i < n; i++)
	{
		if (p[i].y > p2.y && p[i + 1].y <= p2.y)
		{
			if (p[i + 1].y - p[i].y != 0)
			{
				pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x;
			}
			else
			{
				pp[j].x = p[i].x;
			}
			pp[j].y = p2.y;
			j++;
			pp[j].x = p[i + 1].x;
			pp[j].y = p[i + 1].y;
			j++;
		}

		if (p[i].y <= p2.y && p[i + 1].y <= p2.y)
		{
			pp[j].y = p[i + 1].y;
			pp[j].x = p[i + 1].x;
			j++;
		}

		if (p[i].y <= p2.y && p[i + 1].y > p2.y)
		{
			if (p[i + 1].y - p[i].y != 0)
			{
				pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p2.y - p[i].y) + p[i].x;
			}
			else
			{
				pp[j].x = p[i].x;
			}
			pp[j].y = p2.y;
			j++;
		}
	}

	for (i = 0; i < j; i++)
	{
		p[i].x = pp[i].x;
		p[i].y = pp[i].y;
	}

	p[i].x = pp[0].x;
	p[i].y = pp[0].y;
	n = j;
}

void bottom() {
	i = 0; j = 0;

	for (i = 0; i < n; i++)
	{
		if (p[i].y < p1.y && p[i + 1].y >= p1.y)
		{
			if (p[i + 1].y - p[i].y != 0)
			{	// Guardar el punto de interseccion
				pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x;
			}
			else
			{
				pp[j].x = p[i].x;
			}
			pp[j].y = p1.y;
			j++;
			pp[j].x = p[i + 1].x;
			pp[j].y = p[i + 1].y;
			j++;
		}

		if (p[i].y >= p1.y && p[i + 1].y >= p1.y)
		{
			pp[j].x = p[i + 1].x;
			pp[j].y = p[i + 1].y;
			j++;
		}

		if (p[i].y >= p1.y && p[i + 1].y < p1.y)
		{
			if (p[i + 1].y - p[i].y != 0)
			{
				pp[j].x = (p[i + 1].x - p[i].x) / (p[i + 1].y - p[i].y) * (p1.y - p[i].y) + p[i].x;
			}
			else
			{
				pp[j].x = p[i].x;
			}
			pp[j].y = p1.y;
			j++;
		}
	}

	for (i = 0; i < j; i++)
	{
		p[i].x = pp[i].x;
		p[i].y = pp[i].y;
	}
	p[i].x = pp[0].x;
	p[i].y = pp[0].y;
	n = j;
}

void dibujarpoligono() {
	glColor3f(1.0, 0.0, 0.0);
	for (i = 0; i < n - 1; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(p[i].x, p[i].y);
		glVertex2d(p[i + 1].x, p[i + 1].y);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2d(p[i].x, p[i].y);
	glVertex2d(p[0].x, p[0].y);
	glEnd();
}

void myMouse(int boton, int estado, int x, int y) {
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_LOOP);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glVertex2d(p1.x, p2.y);
		glEnd();
		izquierda();
		derecha();
		arriba();
		bottom();
		dibujarpoligono();
	}
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p1.x, p2.y);
	glEnd();
	dibujarpoligono();
	glFlush();
}

void iniciar() {
	glClearColor(0, 0, 0, 0);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
	cout << "Ingrese coordenadas de la ventana: ";
	cout << endl << "Ingrese 2 puntos: " << endl;
	cout << "Ingrese P1(x,y):" << endl;
	cin >> p1.x;
	cin >> p1.y;

	cout << endl << "Ingrese el punto 2 P2(x, y)" << endl;
	cin >> p2.x;
	cin >> p2.y;

	cout << endl << "Ingrese el numero de vertices:";
	cin >> n;

	for (i = 0; i < n; i++)
	{
		cout << endl << "Ingrese V " << i + 1 << "(x, y) : " << endl;
		cin >> p[i].x;
		cin >> p[i].y;
	}

	p[i].x = p[0].x;
	p[i].y = p[0].y;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Algoritmo de Sutherland–Hodgman");
	iniciar();

	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glFlush();
	glutMainLoop();
	return 0;
}