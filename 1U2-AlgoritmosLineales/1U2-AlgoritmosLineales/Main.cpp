#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

struct Point2D {
    GLfloat x;
    GLfloat y;
};Point2D puntoInicial;Point2D puntoFinal;
int click = 1, menuId;

void pintarPunto(int x, int y) {
    glColor3f(0, 0, 1);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(float inicialX, float inicialY, float finalX, float finalY) {
    GLfloat dx = finalX - inicialX;
    GLfloat dy = finalY - inicialY;

    GLfloat step = max(abs(dx), abs(dy));
    GLfloat xi = dx / step;
    GLfloat yi = dy / step;

    GLfloat x = inicialX;
    GLfloat y = inicialY;

    for (int i = 0; i <= step; i++) {
        pintarPunto(x, y);
        x += xi;
        y += yi;
    }
}

void Bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
 
    while (true) {
        pintarPunto(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Draw() {

    if (click == 3) {
        if (menuId == 1) {
            cout << "Dibujando con DDA" << endl;
            DDA(puntoInicial.x, puntoInicial.y, puntoFinal.x, puntoFinal.y);
            
        }
        else if(menuId == 2) {
            cout << "Dibujando con Bresenham" << endl;
            Bresenham(puntoInicial.x, puntoInicial.y, puntoFinal.x, puntoFinal.y);
            
        }

        system("cls");
        cout << "Punto inicial: (" << puntoInicial.x << ", " << puntoInicial.y << ")" << endl;
        cout << "Punto final: (" << puntoFinal.x << ", " << puntoFinal.y << ")" << endl;
        click = 2 ;  // Reiniciar el valor de 'click' despu�s de registrar el segundo clic
        puntoInicial.x = puntoFinal.x; puntoInicial.y = puntoFinal.y;
    }
    glFlush();
}

void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (click == 1) {
            puntoInicial.x = x;
            puntoInicial.y = y;
            
            click = 2;  // Actualizar el valor de 'click' para esperar el segundo clic
        }
        else if (click == 2) {
            puntoFinal.x = x;
            puntoFinal.y = y;
            click = 3;
            glutPostRedisplay();  // Redibujar la escena con la nueva l�nea
        }
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        click = 1;
    }
}

void Menu(int opcion) {
    menuId = opcion;
}

void Init() {
    gluOrtho2D(0, 500, 500, 0);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //menu click
    menuId = glutCreateMenu(Menu);
    glutAddMenuEntry("DDA", 1);
    glutAddMenuEntry("Bresenham", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Algoritmos de dibujo de l�neas");
    Init();
    glutMouseFunc(MouseClick);
    glutDisplayFunc(Draw);
    glutMainLoop();
}


void ViewPort() {
    // Dibujamos el ViewPort o el Marco del Tetris
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    //Vértice de la esquina superior izquierda
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(20, 20);
    //Vértice de la esquina inferior izquierda
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(20, 680);
    //Vértice de la esquina inferior derecha
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(480, 680);
    //Vértice de la esquina superior derecha
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(480, 20);
    glEnd();
}