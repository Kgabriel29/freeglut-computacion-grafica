#include <GL/freeglut.h>
#include <iostream>
#include "Linea.h"
#include "Esfera.h"
using namespace std;

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    LineDrawer line(0.3f, 0.8f, -0.3f, -0.8f);
    line.SetColor(0.0f, 0.0f, 1.0f);
    line.Draw();
    LineDrawer line2(-0.3f, 0.8f, 0.3f, -0.8f);
    line2.SetColor(1.0f, 0.0f, 0.0f);
    line2.SetThik(6);
    line2.Draw();
    //Esfera
    SphereDrawer esfera;
    esfera.SetRadio(0.2);
    esfera.SetColor(1.0f, 1.0f, 0.0f);
    esfera.setPosition(0.0f, -0.8f, 0.0f);
    esfera.Draw();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lineas con Clases");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(Display);
    glutMainLoop();
}
