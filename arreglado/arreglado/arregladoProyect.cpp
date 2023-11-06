#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;
GLint r = 0; GLint g = 0; GLint b = 0; GLint x = 5; GLint y = 5;
struct Vector2D {
    float x;
    float y;
};


void plano(GLint posX, GLint posY) {
    //lineas del palno
    glColor3f(1, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(-posX, 0);
    glVertex2f(posX, 0);
    glVertex2f(0, -posY);
    glVertex2f(0, posY);
    glEnd();
    //puntos del plano
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    for (GLfloat i = -5.0; i <= 5.0; i += 1.0)
    {
        glVertex2f(i, -5.0);
        glVertex2f(i, 5.0);
        glVertex2f(-5.0, i);
        glVertex2f(5.0, i);
    }
    glutPostRedisplay();
    glEnd();
}


void vectoresSuma() {
    Vector2D sumVects,multVect,esca, res;
    
    int numVectors;
    cout << "¿Cuántos vectores ingresará?: ";
    cin >> numVectors;

    vector<Vector2D> vectors(numVectors);
    for (int i = 0; i < numVectors; i++) {
        cout << "Ingrese el vector " << i + 1 << " (x, y): ";
        cin >> vectors[i].x >> vectors[i].y;

        // Dibujar el vector sin operar
        glColor3f(1.0, 0.8, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(vectors[i].x, vectors[i].y);
        glEnd();
        
        // suma vectores
        sumVects.x = vectors[i].x + vectors[i].x;
        sumVects.y = vectors[i].y + vectors[i].y;               
        
    }
  }

void vectoresResta() {
    Vector2D  res;
    
    int numVectors;
    cout << "¿Cuántos vectores ingresará?: ";
    cin >> numVectors;

    vector<Vector2D> vectors(numVectors);
    for (int i = 0; i < numVectors; i++) {
        cout << "Ingrese el vector " << i + 1 << " (x, y): ";
        cin >> vectors[i].x >> vectors[i].y;

        // Dibujar el vector sin operar
        glColor3f(1.0, 0.8, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(vectors[i].x, vectors[i].y);
        glEnd();
        glFlush();        
        
        //resta
        res.x = vectors[i].x - vectors[i].x;
        res.y = vectors[i].y - vectors[i].y;
    }
  }
void vectoresPp() {
    Vector2D sumVects, multVect, esca, res;

    int numVectors;
    cout << "¿Cuántos vectores ingresará?: ";
    cin >> numVectors;

    vector<Vector2D> vectors(numVectors);
    for (int i = 0; i < numVectors; i++) {
        cout << "Ingrese el vector " << i + 1 << " (x, y): ";
        cin >> vectors[i].x >> vectors[i].y;

        // Dibujar el vector sin operar
        glColor3f(1.0, 0.8, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(vectors[i].x, vectors[i].y);
        glEnd();
        glFlush();        

        //producto punto
        multVect.x = vectors[i].x * vectors[i].x + vectors[i].y * vectors[i].y;

        
    }
}
void vectoresEscalar() {
    Vector2D esca;
    int escalar;
    cout << "Ingrese el numero escalar: ";
    cin >> escalar;
    int numVectors;
    cout << "¿Cuántos vectores ingresará?: ";
    cin >> numVectors;

    vector<Vector2D> vectors(numVectors);
    for (int i = 0; i < numVectors; i++) {
        cout << "Ingrese el vector " << i + 1 << " (x, y): ";
        cin >> vectors[i].x >> vectors[i].y;

        // Dibujar el vector sin operar
        glColor3f(1.0, 0.8, 1.0);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(vectors[i].x, vectors[i].y);
        glEnd();
        glFlush();

        //escalar por un vector
        esca.x = vectors[i].x * escalar;
        esca.y = vectors[i].y * escalar;



    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    plano(x,y);

   // vectoresSuma();
   // vectoresResta();
   // vectoresPp();
   // vectoresEscalar();
    glFlush();
}

void colorOpcion(int indice) {
    switch (indice)
    {
    case 1:
        r = 1;
        g = 0;
        b = 0;
        break;

    case 2:
        r = 0;
        g = 1;
        b = 0;
        break;
    case 3:
        r = 0;
        g = 0;
        b = 1;
        break;
    case 4:
        r = 1;
        g = 1;
        b = 0;
        break;
    case 5:
        r = 0;
        g = 1;
        b = 1;
        break;
    case 6:
        r = 0;
        g = 0;
        b = 1;
        break;
    }
}
void mouseClick(int button, int state, int x, int y) {
        
}
void Menu(int opcion) {
    if (opcion == 1) {

    }
}
void createMenu(){ 
    glutCreateMenu(Menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Color", 1);
    glutAddSubMenu("Rojo", 1);
    glutAddSubMenu("Verde", 2);
    glutAddSubMenu("Azul", 3);
   

    glutAddMenuEntry("Dibujar Punto", 4);
    
    glutAddMenuEntry("Dibujar Linea", 3);
    glutAddMenuEntry("Dibujar Cuadrado", 1);
    glutAddMenuEntry("Dibujar Triangulo", 5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("Proyecto Unidad 1");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-x, x, -y, y);   
   // createMenu();
   // glutAttachMenu(GLUT_RIGHT_BUTTON);
   // glutMouseFunc(mouseClick);  
   

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
