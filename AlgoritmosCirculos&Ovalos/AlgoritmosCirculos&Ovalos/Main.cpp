#include <GL/freeglut.h>
#include <cmath>

float posx, posy, radio, radio_x, radio_y;
int click = 1, menuId = 0;

void DrawCirculo(float posX, float posY, float radio) {
    float x = 0;
    float y = radio;
    float p = 1 - radio;
    //se dibuja el punto centro
    glBegin(GL_POINTS);
    glVertex2f(posX, posy);
    glEnd();
        
    glBegin(GL_POINTS);

    while (x <= y) {
        // Cuadrante 1
        glVertex2f(posX + x, posY + y);
        glVertex2f(posX + y, posY + x);

        // Cuadrante 2
        glVertex2f(posX - x, posY + y);
        glVertex2f(posX - y, posY + x);

        // Cuadrante 3
        glVertex2f(posX - x, posY - y);
        glVertex2f(posX - y, posY - x);

        // Cuadrante 4
        glVertex2f(posX + x, posY - y);
        glVertex2f(posX + y, posY - x);

        if (p < 0) {
            p += 2 * x + 3;
        }
        else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }

    glEnd();
}

void DrawOvalo(float posX, float posY, float radioX, float radioY) {
    float radio_cuadrado_x = radioX * radioX;
    float radio_cuadrado_y = radioY * radioY;

    float x = 0;
    float y = radioY;
    float p = radio_cuadrado_y - (radio_cuadrado_x * radioY) + (0.25 * radio_cuadrado_x);

    //se dibuja el punto centro
    glBegin(GL_POINTS);
    glVertex2f(posX, posy);
    glEnd();

    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);

    while ((2 * radio_cuadrado_y * x) < (2 * radio_cuadrado_x * y)) {
        glVertex2f(posX + x, posY + y);
        glVertex2f(posX - x, posY + y);
        glVertex2f(posX - x, posY - y);
        glVertex2f(posX + x, posY - y);

        if (p < 0) {
            p += radio_cuadrado_y * (2 * x + 3);
        }
        else {
            p += radio_cuadrado_y * (2 * x + 3) + radio_cuadrado_x * (-2 * y + 2);
            y--;
        }
        x++;
    }

    p = radio_cuadrado_y * (x + 0.5) * (x + 0.5) + radio_cuadrado_x * (y - 1) * (y - 1) - radio_cuadrado_x * radio_cuadrado_y;

    while (y >= 0) {
        glVertex2f(posX + x, posY + y);
        glVertex2f(posX - x, posY + y);
        glVertex2f(posX - x, posY - y);
        glVertex2f(posX + x, posY - y);

        if (p > 0) {
            p += radio_cuadrado_x * (-2 * y + 3);
        }
        else {
            p += radio_cuadrado_y * (2 * x + 2) + radio_cuadrado_x * (-2 * y + 3);
            x++;
        }
        y--;
    }

    glEnd();
}
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1.0);

    if (click == 4) {
        if (menuId == 1) {
            DrawCirculo(posx, posy, radio);
        }
        else {
            DrawOvalo(posx, posy, radio_x, radio_y);
        }
        click = 1;
    }
    glFlush();
}

void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Valida que sea el primer clic
        if (click == 1) {
            posx = x - 200;
            posy = 200 - y;
            click = 2; // Esperar el segundo clic para determinar el radio
        }
        // Sino, valida si es un segundo clic
        else if (click == 2) {
            GLfloat x_diff = posx - (x - 200);
            GLfloat y_diff = posy - (200 - y);
            radio = sqrt(x_diff * x_diff + y_diff * y_diff);
            click = 4; // Se han dado los dos clics necesarios
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Valida que sea el primer clic
        if (click == 1) {
            posx = x - 200;
            posy = 200 - y;
            click = 2; // Esperar el segundo clic para determinar los radios
        }
        // Sino, valida que sea un segundo clic
        else if (click == 2) {
            GLfloat x_diff = posx - (x - 200);
            GLfloat y_diff = posy - (200 - y);
            radio = sqrt(x_diff * x_diff + y_diff * y_diff);
            click = 3; // Se han dado los dos clics necesarios
        }
        // Caso contrario, se han dado los clics necesarios
        else {
            radio_x = radio;
            GLfloat x_diff = posx - (x - 200);
            GLfloat y_diff = posy - (200 - y);
            radio_y = sqrt(x_diff * x_diff + y_diff * y_diff);
            click = 4; // Se han dado los dos clics necesarios
        }
    }

    glutPostRedisplay(); // Redibujar la escena después del clic
}


void Menu(int opcion) {
    menuId = opcion;
}

void Init() {
    menuId = glutCreateMenu(Menu);
    glutAddMenuEntry("Círculo", 1);
    glutAddMenuEntry("Óvalo", 2);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dibujar Círculo y Ovalo con Punto Medio");
    Init();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-200, 200, -200, 200);

    glutDisplayFunc(Draw);
    glutMouseFunc(MouseClick);
    glutMainLoop();
}