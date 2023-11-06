#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>

void drawPixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawStoneCube() {
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Tamaño de píxel
    float pixelSize = 0.001f;

    // Iterar sobre cada píxel en el cubo
    for (float x = -0.5f; x <= 0.5f; x += pixelSize) {
        for (float y = -0.5f; y <= 0.5f; y += pixelSize) {
            // Generar tonalidad aleatoria de gris
            float grayValue = static_cast<float>(rand()) / RAND_MAX;
            glColor3f(grayValue, grayValue, grayValue);
            drawPixel(x, y);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    drawStoneCube();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo de Piedra");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   
    glutMainLoop();
    return 0;
}
