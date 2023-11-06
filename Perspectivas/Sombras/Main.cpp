#include <GL/freeglut.h>
#include <cmath>
float cameraX = 3.0f;
float cameraZ = 3.0f;
float cameraY = 0.0f;
void drawCube() {
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // Rojo con opacidad completa
    glutSolidCube(1.0f);
}

void drawSphere() {
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f); // Verde con opacidad reducida
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.5f);   // Ajusta la posición
    glutSolidSphere(0.5f, 50, 50);
    glPopMatrix();
}

void drawCone() {
    glColor4f(0.0f, 0.0f, 1.0f, 0.7f); // Azul con opacidad reducida
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, -0.5f); // Ajusta la posición
    glutSolidCone(0.5f, 1.0f, 50, 50);
    glPopMatrix();
}

void drawTorus() {
    glColor4f(1.0f, 1.0f, 0.0f, 0.8f); // Amarillo con opacidad reducida
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, -0.5f); // Ajusta la posición
    glutSolidTorus(0.2f, 0.5f, 50, 50);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawCube();
    drawTorus();
    drawSphere();
    drawCone();

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    float cameraSpeed = 0.1f;

    switch (key) {
    case GLUT_KEY_UP:
        cameraZ -= cameraSpeed;
        break;
    case GLUT_KEY_DOWN:
        cameraZ += cameraSpeed;
        break;
    case GLUT_KEY_LEFT:
        cameraX -= cameraSpeed;
        break;
    case GLUT_KEY_RIGHT:
        cameraX += cameraSpeed;
        break;
    }

    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
    float cameraSpeed = 0.1f;

    switch (key) {
    case 'q':
        cameraY += cameraSpeed;
        break;
    case 'e':
        cameraY -= cameraSpeed;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Algoritmo del Pintor con Movimiento de Cámara");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); // Función para teclas especiales
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}