#include<Windows.h>
#include <gl/freeglut.h>
#include <iostream>

using namespace std;

int xmin = -100, ymin = -100, xmax = 100, ymax = 100;
float m = 0;
float xInicio = 0, yInicio = 0, xFin = 0, yFin = 0;
float x, y;


void display() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 0);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(xInicio, yInicio);
    glVertex2f(xFin, yFin);
    glEnd();
    glFlush();
}
//Codigo binario
int code(float x, float y) {
    int c = 0;
    if (y > ymax) {
        c = 8;  //Parte superior 8 en binario es 1000
    }
    if (y < ymin) {
        c = 4; //Parte inferior 8 en binario es 0100
    }
    if (x > xmax) {
        c = c | 2; //Parte derecha 2 en binario es 0010
    }
    if (x < xmin) {
        c = c | 1; //Parte izquiera 1 en binario es 0001
    }
    return c;
}

void verificarBordes(int c, float xPrueba, float yPrueba) {
    if ((c & 8) > 0) { //Interseca con el borde superior
        y = ymax;
        x = xPrueba + (ymax - yPrueba) / m;
    }
    else if ((c & 4) > 0) { //Interseca con el borde inferior
        y = ymin;
        x = xPrueba + (ymin - yPrueba) / m;
    }
    else if ((c & 2) > 0) { //Interseca con el borde izquierdo
        x = xmax;
        y = yPrueba + m * (xmax - xPrueba);
    }
    else if ((c & 1) > 0) { //Interseca con el borde derecho
        x = xmin;
        y = yPrueba + m * (xmin - xPrueba);
    }
}

void recorte(float x1, float y1, float x2, float y2) {
    int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    //Calculo la pendiente 
    m = (y2 - y1) / (x2 - x1);
    cout << "m=" << m << endl;
    while ((c1 | c2) > 0) { // c1 OR c2 != 0000
        // Al menos uno de los puntos está fuera de la ventana
        if ((c1 & c2) > 0) { // c1 AND c2
            // La línea está completamente fuera de la ventana. Seteamos los puntos iniciales y finales en 0
            xInicio = 0;
            yInicio = 0;
            xFin = 0;
            yFin = 0;
            display();
            return; // Salgo de este módulo
        }
        //Verifica los bordes en caso de que al recortar deba calcular los nuevos puntos
        if (c1 != 0) {
            verificarBordes(c1, xInicio, yInicio);
            xInicio = x;
            yInicio = y;
            c1 = code(xInicio, yInicio);
            cout << "P3(" << xInicio << "," << yInicio << ")" << endl;
        }
        if (c2 != 0) {
            verificarBordes(c2, xFin, yFin);
            xFin = x;
            yFin = y;
            c2 = code(xFin, yFin);
            cout << "P4(" << xFin << "," << yFin << ")" << endl;
        }
    }
    display();
}

void teclado(unsigned char key, int x, int y) {
    if (key == 'r') { // Reinicio
        xInicio = 0;
        yInicio = 0;
        xFin = 0;
        yFin = 0;
        glutPostRedisplay(); // Solicitar una actualización de la ventana
    }
    if (key == 'c') { // Hago el recorte
        recorte(xInicio, yInicio, xFin, yFin);
        glFlush();
    }
    if (key == 27) {
        exit(0);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (xInicio == 0 && yInicio == 0) {
            //Las coordeandas de la ventana arriba e izquierda es 0,0
            //Y las coordenadas de la ventana abajo y derecha es 599,599
            //Se convierten las coordenadas al modelo de vista de coordenadas (VALOR DEL ORTHO)
            xInicio = x - 300;
            yInicio = 300 - y;
            xFin = xInicio;
            yFin = yInicio;
            cout << "P1 (" << xInicio << "," << ")" << yInicio << endl;
        }
        else {
            //Setear las coordeandas al segundo punto (VALOR DEL ORTHO)
            xFin = x - 300;
            yFin = 300 - y;
            cout << "P2(" << xFin << "," << ")" << yFin << endl;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        recorte(xInicio, yInicio, xFin, yFin);
        glFlush();
    }
}
int main(int argc, char** argv) {

    cout << "Haz clic en la ventana para dibujar un segmento de línea." << endl;
    cout << "Presiona la tecla Esc para salir." << endl;
    cout << "Ingresa las coordenadas de la ventana de recorte (xmin, ymin, xmax ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("RECORTE LINEA");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    // Utilizo las teclas para configurar el recorte y reinicio
    //Utilizo r para reiniciar (Pongo nuevos puntos) y c para hacer el recorte con la linea ya hecha
    glutKeyboardFunc(teclado);
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(-300, 300, -300, 300);
    glutMainLoop();
    return 0;
}