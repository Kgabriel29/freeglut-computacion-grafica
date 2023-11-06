#include <GL/glut.h>
#include <iostream>

using namespace std;

float x_min = -100;
float y_min = -100;
float x_max = 100;
float y_max = 100;
float xd1, yd1, xd2, yd2;

int calcularCuadrante(float x, float y)
{
    int cuadrante = 0;
    if (y > y_max) cuadrante = 8;
    if (y < y_min) cuadrante = 4;
    if (x > x_max) cuadrante = cuadrante | 2;
    if (x < x_min) cuadrante = cuadrante | 1;
    return cuadrante;
}

void cohenLinea(float x1, float y1, float x2, float y2)
{
    int cuadrante1 = calcularCuadrante(x1, y1);
    int cuadrante2 = calcularCuadrante(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    while ((cuadrante1 | cuadrante2) > 0)
    {
        if ((cuadrante1 & cuadrante2) > 0)
        {
            exit(0);
        }

        float xi = x1, yi = y1;
        int cuadrante = cuadrante1;
        if (cuadrante == 0)
        {
            cuadrante = cuadrante2;
            xi = x2;
            yi = y2;
        }
        float x, y;
        if ((cuadrante & 8) > 0)
        {
            y = y_max;
            x = xi + 1.0 / m * (y_max - yi);
        }
        else if ((cuadrante & 4) > 0)
        {
            y = y_min;
            x = xi + 1.0 / m * (y_min - yi);
        }
        else if ((cuadrante & 2) > 0)
        {
            x = x_max;
            y = yi + m * (x_max - xi);
        }
        else if ((cuadrante & 1) > 0)
        {
            x = x_min;
            y = yi + m * (x_min - xi);
        }

        if (cuadrante == cuadrante1)
        {
            xd1 = x;
            yd1 = y;
            cuadrante1 = calcularCuadrante(xd1, yd1);
        }

        if (cuadrante == cuadrante2)
        {
            xd2 = x;
            yd2 = y;
            cuadrante2 = calcularCuadrante(xd2, yd2);
        }
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x_min, y_min);
    glVertex2i(x_min, y_max);
    glVertex2i(x_max, y_max);
    glVertex2i(x_max, y_min);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1, yd1);
    glVertex2i(xd2, yd2);
    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'c')
    {
        cohenLinea(xd1, yd1, xd2, yd2);
    }
}

int main(int argc, char** argv)
{
    cout << "Ingrese las coordenadas de la línea (x1 y1 x2 y2): ";
    cin >> xd1 >> yd1 >> xd2 >> yd2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Recorte de línea con Cohen-Sutherland");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);
    glutMainLoop();
    return 0;
}
