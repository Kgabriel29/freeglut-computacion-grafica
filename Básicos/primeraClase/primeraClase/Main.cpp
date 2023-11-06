#include <GL/freeglut.h>
#include <omp.h> // Incluimos la librería para paralelizar

const int width = 800;
const int height = 600;

double xMin = -2.0;
double xMax = 1.0;
double yMin = -1.5;
double yMax = 1.5;

const int maxIterations = 2400;

unsigned char buffer[width * height * 3];

void getColor(int iterations, unsigned char color[3]) {
    color[0] = iterations % 256;
    color[1] = iterations % 128;
    color[2] = iterations % 64;
}

void Mandelbrot() {
    glClear(GL_COLOR_BUFFER_BIT);
#pragma omp parallel for // Paralelizamos el cálculo
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double xPos = xMin + (xMax - xMin) * x / (width - 1);
            double yPos = yMin + (yMax - yMin) * y / (height - 1);

            double zx = 0.0;
            double zy = 0.0;
            int iterations = 0;

            while (zx * zx + zy * zy < 4.0 && iterations < maxIterations) {
                // Aplicamos la fórmula z^3 + c
                double xTemp = zx * zx - zy * zy + xPos;
                zy = 2*zx*zy + yPos;    
                zx = xTemp;
                iterations++;   
            }

            if (iterations == maxIterations) {
                glColor3f(1, 0, 0);
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
           }
           
        }
    }
    
    glFlush();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        xMin -= 0.1 * (xMax - xMin);
        xMax -= 0.1 * (xMax - xMin);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        xMin += 0.1 * (xMax - xMin);
        xMax += 0.1 * (xMax - xMin);
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        yMin -= 0.1 * (yMax - yMin);
        yMax -= 0.1 * (yMax - yMin);
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        yMin += 0.1 * (yMax - yMin);
        yMax += 0.1 * (yMax - yMin);
        glutPostRedisplay();
        break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        xMin += 0.1 * (xMax - xMin);
        xMax -= 0.1 * (xMax - xMin);
        yMin += 0.1 * (yMax - yMin);
        yMax -= 0.1 * (yMax - yMin);
        glutPostRedisplay();
        break;
    case '-':
        xMin -= 0.1 * (xMax - xMin);
        xMax += 0.1 * (xMax - xMin);
        yMin -= 0.1 * (yMax - yMin);
        yMax += 0.1 * (yMax - yMin);
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Fractal de Mandelbrot");
    glutDisplayFunc(Mandelbrot);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}