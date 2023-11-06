#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Vertice {
    GLdouble x;
    GLdouble y;
}; Vertice vertice1, vertice2, vtrian1, vtrian2, vtrian3;


struct Color {
    GLfloat r = 1.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
};
Color color;

GLint Opcion = 1;
GLfloat posX = 0;
GLfloat posY = 0;
bool redibujar = true; int contar = 1; bool dibujar = false;
GLfloat angulo = 0.0f;
GLfloat factorEscala = 1.0f;


void Puntos(GLdouble x, GLdouble y) {
    std::cout << x << "," << y << std::endl;

    glPointSize(5);
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
    glFlush();
}
void Lineas(GLdouble x1, GLdouble x2, GLdouble y1, GLdouble y2) {
    std::cout << x1 << "," << y1 << std::endl;
    std::cout << x2 << "," << y2 << std::endl;

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void Triangulo(GLdouble x1, GLdouble x2, GLdouble x3, GLdouble y1, GLdouble y2, GLdouble y3) {
    std::cout << x1 << "," << y1 << std::endl;
    std::cout << x2 << "," << y2 << std::endl;
    std::cout << x3 << "," << y3 << std::endl;

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);
    glEnd();
    glutSwapBuffers();
    glFlush();
}
void Rotar(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        angulo -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        angulo += 5.0f;
        break;
    }
    glutPostRedisplay(); // Vuelve a dibujar la escena
}

void Escalar(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        factorEscala += 0.1f;
        break;
    case '-':
        factorEscala -= 0.1f;
        break;
    }
    glutPostRedisplay(); // Vuelve a dibujar la escena
}

void drawString(const std::string& str, float x, float y)
{
    glRasterPos2f(x, y);
    for (char c : str) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
    }
}

void plano() {
        glColor3f(0.8, 0.8, 0.8); // Interlineado en color gris

        // Dibujar interlineado
        glBegin(GL_LINES);
        for (float i = -10.0; i <= 10.0; i += 1.0) {
            if (i == 0.0) continue; // Saltar la línea del eje Y
            glVertex2f(i, -10.0);
            glVertex2f(i, 10.0);
            glVertex2f(-10.0, i);
            glVertex2f(10.0, i);
        }
        glEnd();

        glColor3f(0.0, 0.0, 0.0); // Ejes X e Y en color negro

        // Dibujar ejes X e Y
        glBegin(GL_LINES);
        glVertex2f(-10.0, 0.0);
        glVertex2f(10.0, 0.0);
        glVertex2f(0.0, -10.0);
        glVertex2f(0.0, 10.0);
        glEnd();

        // Etiquetas en los ejes X e Y
        glColor3f(0.0, 0.0, 0.0); // Color negro para las etiquetas

        // Etiquetas del eje X
        for (float i = -10.0; i <= 10.0; i += 1.0) {
            if (i != 0.0) {
                std::string label = std::to_string(static_cast<int>(i));
                drawString(label, i - 0.15, -0.75);
            }
        }

        // Etiquetas del eje Y
        for (float i = -10.0; i <= 10.0; i += 1.0) {
            if (i != 0.0) {
                std::string label = std::to_string(static_cast<int>(i));
                drawString(label, -0.75, i - 0.15);
            }
        }

}

void menu(int id) {
    Opcion = id;
}

void initMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Dibujar Punto", 1);
    glutAddMenuEntry("Dibujar Linea", 2);
    glutAddMenuEntry("Dibujar Triángulo", 3);
    glutAddMenuEntry("Dibujar Cuadrado", 4);
    glutAddMenuEntry("Limpiar", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Limpiar() {
    glClear(GL_COLOR_BUFFER_BIT);
    plano();
    redibujar = false;
}

void menuGeogebra(int id) {
    switch (id) {
    case 1:
        if (dibujar == true)
        {
            Puntos(posX, posY);
        }
        dibujar = false;
        break;
    case 2:
        if (dibujar == true) {
            Lineas(vertice1.x, vertice2.x, vertice1.y, vertice2.y);
        }
        dibujar = false;
        break;
    case 3:
        cout << dibujar;
        if (dibujar == true)
        {
            Triangulo(vtrian1.x, vtrian2.x, vtrian3.x, vtrian1.y, vtrian2.y, vtrian3.y);
        }     
        dibujar = false;
        break;
    case 7:
        Limpiar();
        break;
    }
}

void draw() {
    if (redibujar) {
        Limpiar();
    }
    glPushMatrix(); // Guarda la matriz de transformación actual

    // Aplica la rotación
    glTranslatef(posX, posY, 0.0f); // Traslada al centro del objeto
    glRotatef(angulo, 0.0f, 0.0f, 1.0f); // Rota en el eje Z
    glTranslatef(-posX, -posY, 0.0f); // Traslada al origen del objeto

    // Aplica la escala
    glTranslatef(posX, posY, 0.0f); // Traslada al centro del objeto
    glScalef(factorEscala, factorEscala, 1.0f); // Escala en ambos ejes
    glTranslatef(-posX, -posY, 0.0f); // Traslada al origen del objeto

    menuGeogebra(Opcion); // Dibuja el objeto transformado
    glPopMatrix(); // Restaura la matriz de transformación anterior

}

void MouseClick(int button, int state, GLint x, GLint y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //dibujar punto
        if (Opcion == 1) {
            posX = (2.0f * x / 600) * 10.0 - 10;
            posY = 10 - (2.0f * y / 600) * 10.0;
            dibujar = true;
        }
        else if (Opcion == 2) { //dibujar linea
            if (contar == 1) {
                vertice1.x = (2.0f * x / 600) * 10.0 - 10;
                vertice1.y = 10 - (2.0f * y / 600) * 10.0;
                contar = 2;
            }
            else if (contar == 2) {
                vertice2.x = (2.0f * x / 600) * 10.0 -10;
                vertice2.y = 10- (2.0f * y / 600) * 10.0;
                contar = 1;
                dibujar = true;
            }
        }
        else if (Opcion == 3) {//dibujar triangulo
            cout << contar << endl;
            if (contar == 1) {
                cout << "v1" << endl;
                vtrian1.x = (2.0f * x / 600) * 10.0 - 10;
                vtrian1.y = 10- (2.0f * y / 600) * 10.0;
                contar = 2;
            }
            else if (contar == 2) {
                cout << "v2" << endl;
                cout << contar << endl;
                vtrian2.x = (2.0f * x / 600) * 10.0 - 10;
                vtrian2.y = 10 - (2.0f * y / 600) * 10.0;
                contar = 3;
            }
            else if (contar == 3) {
                cout << "v3" << endl;
                cout << contar << endl;
                vtrian3.x = (2.0f * x / 600) * 10.0 - 10;
                vtrian3.y = 10 - (2.0f * y / 600) * 10.0;
                contar = 1;
                cout << contar << endl;
                dibujar = true;
                draw();
            }
        }
    }
}


void subcolor(int indice) {
    switch (indice) {
    case 1:
        color.r = 1;
        color.g = 0;
        color.b = 0;
        break;
    case 2:
        color.r = 0;
        color.g = 1;
        color.b = 0;
        break;
    case 3:
        color.r = 0;
        color.g = 0;
        color.b = 1;
        break;
    case 4:
        color.r = 0.588;
        color.g = 0.294;
        color.b = 0;
        break;
    case 5:
        color.r = 1;
        color.g = 1;
        color.b = 0;
        break;
    case 6:
        color.r = 1;
        color.g = 0;
        color.b = 1;
        break;
    case 7:
        color.r = 0;
        color.g = 1;
        color.b = 1;
        break;
    case 8:
        color.r = 1;
        color.g = 0.5;
        color.b = 0;
        break;
    case 9:
        color.r = 0.5;
        color.g = 0;
        color.b = 1;
        break;
    case 10:
        color.r = 1;
        color.g = 0.5;
        color.b = 0.5;
        break;
    }
}

void colorMenu() {
    glutCreateMenu(subcolor);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);
    glutAddMenuEntry("Cafe", 4);
    glutAddMenuEntry("Amarillo", 5);
    glutAddMenuEntry("Magenta", 6);
    glutAddMenuEntry("Cian", 7);
    glutAddMenuEntry("Naranja", 8);
    glutAddMenuEntry("Violeta", 9);
    glutAddMenuEntry("Rosado", 10);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Proyecto Geogebra - Grupo 2");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-10, 10, -10, 10);

    glutMouseFunc(MouseClick);
    glutSpecialFunc(Rotar); // Registra la función Rotar() para las teclas especiales
    glutKeyboardFunc(Escalar); // Registra la función Escalar() para las teclas normales

    initMenu();
    menu(Opcion);
    colorMenu();

    glutDisplayFunc(draw);
    glutMainLoop();
}