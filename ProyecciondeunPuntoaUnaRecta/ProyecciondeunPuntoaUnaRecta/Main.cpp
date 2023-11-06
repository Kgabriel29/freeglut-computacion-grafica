/*Libreria usada solo en Windows - debe ir antes que las dem�s librerias */
#include<windows.h>
/*Librer�a de OpenGL*/
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

//Declaramos las variables necesarias para almacenar las coordenadas 
//de los v�rtices tanto de la recta como las coordenadas del punto P.
GLfloat P[] = { -4 , 3 }; GLfloat A[] = { -3 , -5 }; GLfloat B[] = { 2 , 5 }; GLfloat m = 0;

//Definimos una funci�n para generar un plano cartesiano
void plano(GLfloat x, GLfloat y) {
    glColor3f(0, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(-x, 0);
    glVertex2f(x, 0);

    glVertex2f(0, -y);
    glVertex2f(0, y);
    glEnd();
    glPointSize(5);
    glColor3f(1, 0, 0);
    for (GLfloat i = -x + 1; i < x; i++)
    {
        glBegin(GL_POINTS);
        glVertex2f(i, 0);
        glVertex2f(0, i);
    }
    glEnd();
}

//Definimos la funci�n que nos dar� la representaci�n visual del punto y la recta
void drawDatos() {

    glColor3f(0.0, 1.0, 0.0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0.0, 1.0, 0.2);
    glVertex2f(P[0], P[1]);
    glVertex2f(A[0], A[1]);
    glVertex2f(B[0], B[1]);
    glEnd();

    //generar recta 
    glLineWidth(5);
    glColor3f(0.3, 0.0, 0.8);
    glBegin(GL_LINES);  
    glVertex2f(B[0], B[1]);
    glVertex2f(A[0], A[1]);
   
    glEnd();
}
//Definimos una funci�n para el c�lculo del �rea
void Calculos() {
    //C�lculo de la pendiente opesta a la recta
    GLfloat m1 = ((B[1] - A[1]) / (B[0] - A[0]));
    cout << "La pendiente de la recta AB ES: " << m1 << endl;
    m = ((-1) / m1);
    cout << "La pendiente de la recta perpendicular a AB ES: " << m << endl << endl;
    cout << "El sistema de ecuaciones quedaria asi:" << endl;
    cout << "2x + y = 1" << endl;
    cout << "1/2x + y = 1" << endl;
    GLfloat r1[] = { 2,1,1 }; GLfloat r2[] = { 1 / 2, 1, 1 };

    GLfloat determinante = (r1[0] * r2[1]) - (r2[0] * r1[1]);
    if (determinante == 0) {
        // El sistema no tiene soluci�n �nica
        cout << "El sistema no tiene una solucion unica." << endl;
    }
    else {
        //cout << "(" << r1[1] << "*" << r2[2] << ") -(" << r2[1] << "*" << r1[2]<<"))/" << determinante<<endl;
        GLfloat x = ((r1[1] * r2[2]) - (r2[1] * r1[2]) )/ determinante;
        GLfloat y = ((r1[0] * r2[2]) - (r2[0] * r1[2])) / determinante;
        cout << "La proyeccion del punto P a la recta es:(" << x << "," << y << ")" << endl;
        glLineWidth(4);
        glColor3f(1, 0, 0.3);
        glBegin(GL_LINES);
        glVertex2f(P[0], P[1]);
        glVertex2f(x, y);
        glEnd();
        glColor3f(0, 1, 0);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        
    }
}

//Funci�n para la representaci�n del plano y el pol�gono
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawDatos();
    plano(7, 7);
    Calculos();
    glFlush();
}



//Configuramos la funci�n principal de nuestro programa

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Representaci�n de pol�gono y c�lculo de �rea");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-7.0, 7.0, -7.0, 7.0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

