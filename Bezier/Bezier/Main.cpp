    #include <GL/freeglut.h>
    #include <iostream>
    using namespace std;
    GLfloat a1, b1, a2, b2, a3, b3, a4, b4;
    int click = 1, menuId = 1;

    void DrawPoints(GLfloat x, GLfloat y) {
        glColor3f(0, 1, 1);
        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }

    void Bezier2() {
        GLfloat t;
        const int numSegments = 100;

        for (int i = 1; i <= numSegments; ++i) {
            t = GLfloat(i) / GLfloat(numSegments);

            // Cálculo de los puntos a lo largo de la curva de Bézier
            GLfloat px = (1 - t) * (1 - t) * a1 + 2 * (1 - t) * t * a2 + t * t * a3;
            GLfloat py = (1 - t) * (1 - t) * b1 + 2 * (1 - t) * t * b2 + t * t * b3;

            // Dibuja el punto en la posición calculada
            DrawPoints(px, py);
        }
    }

    void Bezier3() {
        GLfloat t;
        const int numSegments = 1000;

        for (int i = 1; i <= numSegments; ++i) {
            t = GLfloat(i) / GLfloat(numSegments);

            // Cálculo de los puntos a lo largo de la curva de Bézier
                GLfloat px = pow(1 - t, 3) * a1 + 3 * pow(1 - t, 2) * t * a2 + 3 * (1 - t) * pow(t, 2) * a3 + pow(t, 3) * a4;
                GLfloat py = pow(1 - t, 3) * b1 + 3 * pow(1 - t, 2) * t * b2 + 3 * (1 - t) * pow(t, 2) * b3 + pow(t, 3) * b4;

            // Dibuja el punto en la posición calculada
            DrawPoints(px, py);
        }
    }

    void MouseClick(int button, int state, int x, int y) {

        if (menuId == 1) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

                if (click == 1) {
                    //toma los datos del primer punto
                    a1 = x;
                    b1 = y;
                    click = 2;
                }
                else if (click == 2) {
                    //toma los datos del segundo punto
                    a2 = x;
                    b2 = y;
                    click = 3;
                }
                else {
                    //toma los datos del tercer punto
                    a3 = x;
                    b3 = y;
                    click = 4;
                }
            }
        }
        else if (menuId == 2) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

                if (click == 1) {
                    //toma los datos del primer punto
                    a1 = x;
                    b1 = y;
                    click = 2;
                }
                else if (click == 2) {
                    //toma los datos del segundo punto
                    a2 = x;
                    b2 = y;
                    click = 3;
                }
                else if (click == 3) {
                    //toma los datos del tercer punto
                    a3 = x;
                    b3 = y;
                    click = 4;
                }
                else {
                    //toma los datos del cuarto punto
                    a4 = x;
                    b4 = y;
                    click = 5;
                }
            }
        }
        glutPostRedisplay();
    }
    void Draw() {

        if (click == 4) {
            if (menuId == 1) {
                Bezier2();
                click = 1;
            }
        }
        else if (click == 5) {
            if (menuId == 2) {
                Bezier3();
                click = 1;
            }
        }
        glFlush();
    }

    void Menu(int opcion) {
        menuId = opcion;
    }

    void Init() {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        menuId = glutCreateMenu(Menu);
        glutAddMenuEntry("Bezier Cuadratica", 1);
        glutAddMenuEntry("Bezier Cubica", 2);
        glutAttachMenu(GLUT_MIDDLE_BUTTON);
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Algoritmos de Curvas");
        Init();
        gluOrtho2D(0, 500, 500, 0);
        glutDisplayFunc(Draw);
        glutMouseFunc(MouseClick);
        glutMainLoop();
    }
