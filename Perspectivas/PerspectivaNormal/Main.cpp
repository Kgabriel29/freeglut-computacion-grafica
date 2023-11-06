#include <GL/freeglut.h>

// Variables globales
GLfloat lightPosition[] = { 100.0, 180.0f, 0.0f, 0.0f };
GLfloat teapotPosition[] = { 0.0f, 0.0f, 0.0f };
GLfloat floorShadow[16];

// Variables para controlar la rotaci�n de la figura
GLfloat rotationAngle = 0.0f;
GLfloat rotationSpeed = 0.5f;

// Variables para el manejo del mouse
int previousMouseX = 0;
int previousMouseY = 0;
bool isLeftButtonPressed = false;

// Funci�n para dibujar la escena
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configurar la posici�n de la luz
    glLightfv(GL_LIGHT0, GL_FRONT_AND_BACK, lightPosition);

    // Configurar la vista de la c�mara
    glMatrixMode(GL_MODELVIEW);
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 500.0f, // Posici�n de la c�mara
        0.0f, 0.0f, 0.0f, // Punto de mira
        0.0f, 1.0f, 0.0f); // Vector arriba
    glColor3f(1, 1, 0);
    glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]); // Posici�n de la fuente de luz
    glutSolidSphere(50, 100, 100);
    // Rotar la figura
    glRotatef(rotationAngle, 0.0f, 1.0f, 1.0f);

    // Dibujar la tetera
    glPushMatrix();
    glTranslatef(teapotPosition[0], teapotPosition[1], teapotPosition[2]);
    glutSolidTeapot(100.0);
    glPopMatrix();

    // Dibujar la sombra del objeto
    
    glDisable(GL_LIGHTING); //deshabilita la iluminaci�n para que la sombra no se vea afectada por las fuentes de luz en la escena
    glDisable(GL_DEPTH_TEST); //deshabilita el z-buffer para que la sombra pueda ser dibujada incluso si hay objetos delante de ella en t�rminos de profundidad
    glEnable(GL_BLEND); //habilita el mezclado de colores para lograr una apariencia transparente de la sombra
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //establece la funci�n de mezclado de colores para el mezclado alfa (alpha blending), lo que permite que la sombra tenga transparencia
    glPushMatrix(); //guarda la matriz de transformaci�n actual.
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f); //rgb y la transparencia
    glTranslatef(0, 0.0, 0); //realiza una traslaci�n para posicionar la sombra cerca del objeto.
    glutSolidTeapot(100.0);// dibuja la tetera de la sombra utilizando la funci�n glutSolidTeapot().
    glPopMatrix();
    glDisable(GL_BLEND); //habilitar el z-buffer
    glEnable(GL_DEPTH_TEST); //vuelve a habilitar la iluminaci�n
    glEnable(GL_LIGHTING); //restaurar la configuraci�n original despu�s de dibujar la sombra.

    glutSwapBuffers();
}

// Funci�n para inicializar OpenGL
void initOpenGL() {
    glOrtho(-100, 100, -100, 100, 100, 100);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  //luz on la que se trabaja
    glEnable(GL_COLOR_MATERIAL); //sigue el material de color, utilizara el blanco 
    glEnable(GL_DEPTH_TEST); // Habilita el z-buffer, tambi�n conocido como el buffer de profundidad
    glShadeModel(GL_SMOOTH); //sombreado para aperiencia suave y realista
    glEnable(GL_NORMALIZE); //habilita la normalizaci�n autom�tica de los vectores normales en la escena.

    // Cambiar la configuraci�n de la proyecci�n a una proyecci�n ortogr�fica isom�trica
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
}


// Funci�n para manejar el redimensionamiento de la ventana
void handleResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
}

// Funci�n para manejar los eventos del teclado
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        teapotPosition[1] += 0.1f;
        break;
    case 's':
    case 'S':
        teapotPosition[1] -= 0.1f;
        break;
    case 'a':
    case 'A':
        teapotPosition[0] -= 0.1f;
        break;
    case 'd':
    case 'D':
        teapotPosition[0] += 0.1f;
        break;
    case 'q':
    case 'Q':
        teapotPosition[2] -= 0.1f;
        break;
    case 'e':
    case 'E':
        teapotPosition[2] += 0.1f;
        break;
    }

    glutPostRedisplay();
}

// Funci�n para manejar los eventos del mouse
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isLeftButtonPressed = true;
            previousMouseX = x;
            previousMouseY = y;
        }
        else if (state == GLUT_UP) {
            isLeftButtonPressed = false;
        }
    }
}

// Funci�n para manejar el movimiento del mouse
void handleMouseMove(int x, int y) {
    if (isLeftButtonPressed) {
        int deltaX = x - previousMouseX;
        int deltaY = y - previousMouseY;
        rotationAngle += rotationSpeed * deltaX;
        previousMouseX = x;
        previousMouseY = y;
        glutPostRedisplay();
    }
}

// Funci�n principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tetera con sombra en OpenGL");
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    initOpenGL();
    glutMainLoop();
    return 0;
}