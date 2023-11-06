#include <GL/freeglut.h>
#include <iostream>
#include <vector>

std::vector<GLfloat> controlPointsX;
std::vector<GLfloat> controlPointsY;
int numControlPoints = 0;
void plano() {
    // Dibujar la cuadrícula en el fondo
    glColor3f(0.5, 0.5, 0.5);//COLOR GRIS
    glLineWidth(1.0);

    glBegin(GL_LINES);

    for (float i = -1.0; i <= 1.0; i += 0.1)
    {
        //lineas verticales
        glVertex2f(-1.0, i);
        glVertex2f(1.0, i);

        //lineas horizontales
        glVertex2f(i, -1.0);
        glVertex2f(i, 1.0);
    }

    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    //color para el eje x
    glColor3f(1.0, 0.0, 0.0);
    //linea para el eje x
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    //colo para el eje y
    glColor3f(0.0, 1.0, 0.0);

    //linea para el eje y
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

}

GLfloat bSplineMatrix[][4] = {
    {-1.0 / 6, 3.0 / 6, -3.0 / 6, 1.0 / 6},
    {3.0 / 6, -6.0 / 6, 3.0 / 6, 0.0},
    {-3.0 / 6, 0.0, 3.0 / 6, 0.0},
    {1.0 / 6, 4.0 / 6, 1.0 / 6, 0.0}
};

// Función para calcular el valor de base B-Spline
GLfloat bSplineBasis(int i, int k, GLfloat t)
{
    if (k == 0)
    {
        if (t >= i && t < i + 1)
            return 1.0;
        return 0.0;
    }

    GLfloat b1 = (t - i) / (k + 1) * bSplineBasis(i, k - 1, t);
    GLfloat b2 = (i + k + 1 - t) / (k + 1) * bSplineBasis(i + 1, k - 1, t);

    return b1 + b2;
}

// Función para calcular el punto en la Curva B-Spline
void calculatePointBSpline(GLfloat t, GLfloat point[2])
{
    point[0] = 0.0;
    point[1] = 0.0;

    for (int i = 0; i < numControlPoints; i++)
    {
        GLfloat basis = bSplineBasis(i, 3, t);
        point[0] += basis * controlPointsX[i];
        point[1] += basis * controlPointsY[i];
    }
}

// Función de renderizado
void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    plano();
    glColor3f(0.0, 1.0, 0.0);

    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
    for (GLfloat t = 0.0; t <= numControlPoints - 3; t += 0.01)
    {
        GLfloat point[2];
        calculatePointBSpline(t, point);
        glVertex2fv(point);
    }
    glEnd();

    glFlush();
}

// Función para añadir un punto de control
void addControlPoint(int x, int y)
{
    // Normalizamos las coordenadas del punto en el rango [-1, 1]
    GLfloat normalizedX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
    GLfloat normalizedY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);

    controlPointsX.push_back(normalizedX);
    controlPointsY.push_back(normalizedY);
    numControlPoints++;
}

// Función de callback para capturar clics del ratón
void mouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        addControlPoint(x, y);
        glutPostRedisplay();
    }
}

// Función principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Curva B-Spline");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(renderScene);
    glutMouseFunc(mouseCallback);
    glutMainLoop();
}