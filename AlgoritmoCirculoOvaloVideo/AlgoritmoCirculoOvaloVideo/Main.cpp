#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
using namespace std;

int Alto = 500, Ancho = 500;
double a, b, x, y;

void pintaPixel(int x, int y, int r, int g, int b) {
    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void pintaElipse() {
    double elipsx, elipsy;
    double a2 = a * a;
    double b2 = b * b;
    elipsx = -a;

    while (elipsx <= a) {
        elipsy = b * sqrt(1 - (elipsx * elipsx) / a2);

        pintaPixel(elipsx + x, elipsy + y, 0, 0, 1);
        pintaPixel(elipsx + x, -elipsy + y, 0, 0, 1);

        elipsx += 0.1; // Incremento más pequeño para suavizar la forma de la elipse
    }
}

void raton(int btn, int state, int x1, int y1) {
    y1 = Alto / 2 - y1;
    x1 = x1 - Ancho / 2;
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        a = abs(x1);
        b = abs(y1);
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        x = x1;
        y = y1;
        pintaElipse();
    }
}


void ejes() {
    for (int i = -Ancho / 2; i <= Ancho / 2; i++) {
        pintaPixel(i, 0, 0, 0, 0);
    }
    for (int j = -Alto / 2; j <= Alto / 2; j++) {
        pintaPixel(0, j, 0, 0, 0);
    }
    glutMouseFunc(raton);
    glFlush();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    ejes();
    pintaElipse();
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(Alto, Ancho);
    glutCreateWindow("Pintar elipse");
    gluOrtho2D(-Ancho / 2, Ancho / 2, -Alto / 2, Alto / 2);
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(draw);
    glutMainLoop();

}
