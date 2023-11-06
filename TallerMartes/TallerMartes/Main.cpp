#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <vector>

using namespace std;

GLfloat tranX, tranY;
GLfloat scalaX, scalaY, angulo;

//Estructura de punto
struct Point2D
{
    GLfloat x;
    GLfloat y;
    Point2D(GLfloat _x, GLfloat _y) : x(_x), y(_y) {}
};
//Estructura para el control de lineas
struct Line2D
{
    Point2D inicio;
    Point2D fin;
    Line2D(const Point2D& _inicio, const Point2D& _fin) : inicio(_inicio), fin(_fin) {}
};

struct Poligono {
    vector<Line2D> lineas;
}; Poligono poligono;

//Varibales para genera un linea
Line2D lineaOriginal(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f));
Line2D lineaTrasladada(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f));

void DrawPoligon() {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);//aplica el color de la pantalla
    glBegin(GL_LINES);
    // Dibujar todas las líneas del polígono
    for (const auto& linea : poligono.lineas) {
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(linea.inicio.x, linea.inicio.y);
        glVertex2f(linea.fin.x, linea.fin.y);
    }
    glEnd();

    GLfloat matrix[16] = {

        scalaX * cos(angulo) , scalaY * sin(angulo), 0.0, 0.0,
        -scalaX * sin(angulo), scalaY * cos(angulo), 0.0, 0.0,
        0.0                  , 0.0                 , 1.0, 0.0,
        tranX                , tranY               , 0.0, 1.0

    };

    glMultMatrixf(matrix);

    glBegin(GL_LINES);
    // Dibujar las líneas trasladadas
    for (const auto& linea : poligono.lineas) {
        glColor3f(1.0, 0.0, 0.2);
        glVertex2f(linea.inicio.x, linea.inicio.y);
        glVertex2f(linea.fin.x, linea.fin.y);
    }
    glEnd();


}

void Draw()
{
    DrawPoligon();//dibujamos la línea para implementar los movimientos   
    glFlush();
}
void Init() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// carga la matriz de identidad
    glOrtho(-10, 10, -10, 10, -1.0, 1.0);
}

void IngresoDatos() {
    // Obtener el número de lados del polígono
    int n;
    cout << "Ingrese el número de lados del polígono: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        // Obtener las coordenadas de cada línea
        GLfloat iniX, iniY, finX, finY;
        cout << "Ingrese las coordenadas de la línea " << i + 1 << " (inicioX, inicioY, finX, finY): ";
        cin >> iniX >> iniY >> finX >> finY;

        // Agregar la línea al vector de líneas del polígono
        poligono.lineas.push_back(Line2D(Point2D(iniX, iniY), Point2D(finX, finY)));
    }
    cout << "Ingrese la traslación del poligono ( x , y ): ";
    cin >> tranX >> tranY;
    cout << "Ingrese los valores para la escala ( x , y ): ";
    cin >> scalaX >> scalaY;
    cout << "Ingrese el angulo de rotacion (GRADOS): ";
    cin >> angulo;
}

int main(int argc, char** argv)
{
    //Obtener valores por teclado
    IngresoDatos();
    //inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Taller1U2");

    Init();
    glutDisplayFunc(Draw);
    glutMainLoop();
}