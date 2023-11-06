#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>

using namespace std;

float angle = 0.0;
float scale = 1.0;
float translationX = 0.0;
float translationY = 0.0;

void display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // Dibujar la cuadrícula en el fondo
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (float i = -1.0; i <= 1.0; i += 0.1)
    {
        glVertex2f(-1.0, i);
        glVertex2f(1.0, i);
        glVertex2f(i, -1.0);
        glVertex2f(i, 1.0);
    }

    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();


    // Realizar las transformaciones
    GLfloat matrix[16] = {

        scale * cos(angle) , scale * sin(angle), 0.0, 0.0,
        -scale * sin(angle), scale * cos(angle), 0.0, 0.0,
        0.0                , 0.0               , 1.0, 0.0,
        translationX       , translationY      , 0.0, 1.0

    };


    glMultMatrixf(matrix);//multiplica la matris transformacion por la matriz actual 


    // Dibujar la cuadrícula en el fondo
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (float i = -1.0; i <= 1.0; i += 0.1)
    {
        glVertex2f(-1.0, i);
        glVertex2f(1.0, i);
        glVertex2f(i, -1.0);
        glVertex2f(i, 1.0);
    }

    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.6, -0.6);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.6, -0.6);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.6);
    glEnd();

    glFlush();
}

void valores()
{
    system("cls");
    cout << "////////////  CAMBIO DE COORDENADAS  ////////////" << endl;
    cout << "/--------------------------------------------/" << endl;
    cout << "/ Teclas para traslación: w, a, s, d         /" << endl;
    cout << "/ Teclas para rotación: q, e                 /" << endl;
    cout << "/ Teclas para escala: x, z                   /" << endl;
    cout << "/--------------------------------------------/" << endl;
    cout << "/                  DATOS                     /" << endl;
    cout << "/ Escala: " << scale << endl;
    cout << "/ Rotacion: " << angle << endl;
    cout << "/ Traslacion en X: " << translationX << endl;
    cout << "/ Traslacion en Y: " << translationY << endl;
    cout << "/--------------------------------------------/" << endl;
    cout << endl;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': // Mover hacia arriba
        translationY += 0.1;
        valores();
        break;
    case 's': // Mover hacia abajo
        translationY -= 0.1;
        valores();
        break;
    case 'a': // Mover hacia la izquierda
        translationX -= 0.1;
        valores();
        break;
    case 'd': // Mover hacia la derecha
        translationX += 0.1;
        valores();
        break;
    case 'q': // Rotar en sentido antihorario
        angle += 0.1;
        valores();
        break;
    case 'e': // Rotar en sentido horario
        angle -= 0.1;
        valores();
        break;
    case 'z': // Aumentar escala
        scale += 0.1;
        valores();
        break;
    case 'x': // Disminuir escala
        scale -= 0.1;
        valores();
        break;
    case 'r': // Reiniciar las transformaciones
        angle = 0.0;
        scale = 1.0;
        translationX = 0.0;
        translationY = 0.0;
        valores();
        break;
    default:
        cout << "No se reconoce la tecla. Verifique que las teclas no estén en mayúsculas." << endl;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformaciones 2D sin OpenGL");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    valores();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}