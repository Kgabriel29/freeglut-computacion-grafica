#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mmsystem.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

GLfloat light_position1[] = { 0.5f, -0.3f, 2.0f }; 
GLfloat light_position2[] = { 0.0f, -0.3f, -3.0f }; 
GLfloat light_position3[] = { 2.0f, -0.3f, -3.0f }; 
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; 



bool gameover = false;
GLuint texture[1];
int width, height, nrChannels;
unsigned char* data = stbi_load("rose.jpg", &width, &height, &nrChannels, 0);
//unsigned char* data1 = stbi_load("images.jpg", &width, &height, &nrChannels2, 0);

void cargarTextura(unsigned char* archivo, int index) {
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glGenTextures(1, &texture[index]);
    glBindTexture(GL_TEXTURE_2D, texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, archivo);
    stbi_image_free(archivo);
}
void dibujarplano() {

    // Dibujar ejes x, y, z
    glBegin(GL_LINES);

    // Eje x (rojo)
    GLfloat ejex[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ejex);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);

    // Eje y (verde)
    GLfloat ejey[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ejey);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);

    // Eje z (azul)
    GLfloat ejez[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ejez);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);

    glEnd();

}

void renderText(const char* text, int x, int y) {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for (const char* c = text; *c; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}

int puntos = 0;
int intentos = 3;

struct Sphere {
    float x, y, z;
    float radius;
};

//dificultades: radio 0.05 dificil, radio 0.1 normal, radio 0.3 facil
GLfloat dificultad = 0.3f;


Sphere targetSphere = { 0.0f, 0.0f, 0.0f, dificultad };
bool aiming = false;

void renderSphere(float x, float y, float z, float radius) {
    glPushMatrix();
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}

void renderCube() {
    // Definir los colores de las caras
    GLfloat colors[6][3] = {
        {1.0f, 0.0f, 0.0f},  // Cara frontal (rojo)
        {0.0f, 1.0f, 0.0f},  // Cara trasera (verde)
        {0.0f, 0.0f, 1.0f},  // Cara derecha (azul)
        {1.0f, 1.0f, 0.0f},  // Cara izquierda (amarillo)
        {1.0f, 0.0f, 1.0f},  // Cara superior (magenta)
        {0.0f, 1.0f, 1.0f}   // Cara inferior (cyan)
    };

    GLfloat gris[3] = { 0.5f, 0.5f, 0.5f };
    GLfloat gris2[3] = { 0.4f, 0.4f, 0.4f };

    GLfloat suelo[3] = { 0.2f, 0.2f, 0.2f };
    glEnable(GL_TEXTURE_2D);   
    
    glBegin(GL_QUADS);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,gris2);  

    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, 2.0f, -4.0f);
    glVertex3f(3.0f, 2.0f, -4.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, suelo);
    glNormal3f(1.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, -0.3f, 2.0f);
    glVertex3f(3.0f, -0.3f, 2.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris); 
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-3.0f, 2.0f, -4.0f);
    glVertex3f(3.0f, 2.0f, -4.0f);
    glVertex3f(3.0f, 2.0f, 2.0f);
    glVertex3f(-3.0f, 2.0f, 2.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-3.0f, -0.3f, 2.0f);
    glVertex3f(3.0f, -0.3f, 2.0f);
    glVertex3f(3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, -0.3f, -4.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris); 
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 2.0f, -4.0f);
    glVertex3f(3.0f, -0.3f, -4.0f);
    glVertex3f(3.0f, -0.3f, 2.0f);
    glVertex3f(3.0f, 2.0f, 2.0f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris); 
    glNormal3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-3.0f, 2.0f, -4.0f);
    glVertex3f(-3.0f, -0.3f, -4.0f);
    glVertex3f(-3.0f, -0.3f, 2.0f);
    glVertex3f(-3.0f, 2.0f, 2.0f);

    glEnd();        
    glDisable(GL_TEXTURE_2D);   
    glFlush(); 
}


bool pointInsideSphere(float pointX, float pointY, const Sphere& sphere) {
    float distance = std::sqrt(
        std::pow(pointX - sphere.x, 2) +
        std::pow(pointY - sphere.y, 2)
    );
    return distance <= sphere.radius;
}

void generateNewTargetSphere() {
    targetSphere.x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5.4f)) - 2.7f; // Números entre -2.7 y 2.7
    targetSphere.y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.7f));       // Números entre 0 y 1.7
    targetSphere.z = static_cast<float>(rand() % 3 - 4);
}

void mouseCallback(int button, int state, int x, int y) {
    if (!gameover && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        aiming = true;
        PlaySound(TEXT("l.wav"), NULL, SND_ASYNC | SND_FILENAME);
        float normalizedX = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
        float normalizedY = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT);

        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        winX = normalizedX * viewport[2] / 2 + viewport[2] / 2;
        winY = normalizedY * viewport[3] / 2 + viewport[3] / 2;
        glReadPixels(int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        if (pointInsideSphere(posX, posY, targetSphere)) {
            std::cout << "Apuntaste a la esfera." << std::endl;
            PlaySound(TEXT("punto.wav"), NULL, SND_ASYNC | SND_FILENAME);
            generateNewTargetSphere();
            puntos += 100;

        }
        else {
            std::cout << "No apuntaste a la esfera." << std::endl;
            PlaySound(TEXT("laser.wav"), NULL, SND_ASYNC | SND_FILENAME);

            intentos--;

            if (intentos <= 0) {

                gameover = true;
            }

        }
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        aiming = false;
    }
}

void datosPantalla() {

    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    renderText("---------------------------------TABLERO---------------------------------", 10, 140);
    renderText("SALIR (E)", 40, 50);
    renderText("DIFICULTAD ACTUAL:", 20, 100);

    if (dificultad == 0.5f) {

        glColor3f(0.0f, 1.0f, 0.0f);
        renderText("FACIL", 220, 100);
    }
    if (dificultad == 0.3f) {

        glColor3f(1.0f, 1.0f, 0.0f);
        renderText("NORMAL", 220, 100);
    }
    if (dificultad == 0.05f) {

        glColor3f(1.0f, 0.0f, 0.0f);
        renderText("DIFICIL", 220, 100);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    renderText("DIFICULTAD:", 320, 100);
    glColor3f(0.0f, 1.0f, 0.0f);
    renderText("FACIL PRESS F", 340, 80);
    glColor3f(1.0f, 1.0f, 0.0f);
    renderText("NORMAL PRESS N", 340, 60);
    glColor3f(1.0f, 0.0f, 0.0f);
    renderText("DIFICIL PRESS D", 340, 40);
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    renderText("SCORE:", 600, 80);
    char puntosStr[10];  // Buffer para almacenar la cadena de puntos
    sprintf_s(puntosStr, "%d", puntos);  // Convierte el entero a cadena
    renderText(puntosStr, 675, 80);
    renderText("intentos: ", 600, 40);
    char intentosStr[10];  // Buffer para almacenar la cadena de puntos
    sprintf_s(intentosStr, "%d", intentos);  // Convierte el entero a cadena
    renderText(intentosStr, 675, 40);

    if (gameover) {
        glColor3f(1.0f, 0.0f, 0.0f);
        renderText("JUEGO TERMINADO R PARA REINICIAR", 200, 400);
        PlaySound(TEXT("error.wav"), NULL, SND_ASYNC | SND_FILENAME);
    }


}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    datosPantalla();


    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    //glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);

    glDisable(GL_LIGHT1);
    gluLookAt(0.0f, 1.0f, 0.3f, 0.0f, 0.0f, -5.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -5.0f);


    glPushMatrix();
    GLfloat yellow_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow_diffuse);
    glNormal3f(1.0f, 1.0f, 1.0f);
    renderSphere(targetSphere.x, targetSphere.y, targetSphere.z, targetSphere.radius);
    glPopMatrix();


    glEnable(GL_LIGHT1);
    glPushMatrix();
    renderCube();
    glPopMatrix();

    glutSwapBuffers();

}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 1.0f, 100.0f);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void keyboardCallback(unsigned char key, int x, int y) {
    if (!gameover) {
        switch (key) {
        case 'f':
        case 'F':
            dificultad = 0.5f;
            puntos = 0;
            intentos = 6;
            break;
        case 'D':
        case 'd':
            dificultad = 0.05f;
            puntos = 0;
            intentos = 2;
            break;
        case 'n':
        case 'N':
            dificultad = 0.3f;
            puntos = 0;
            intentos = 3;
            break;
        }

        targetSphere.radius = dificultad;
    }
    switch (key) {
    case 'R':
    case 'r':
        dificultad = 0.3f;
        puntos = 0;
        intentos = 3;
        gameover = false;
        PlaySound(TEXT("reinicio.wav"), NULL, SND_ASYNC | SND_FILENAME);
        generateNewTargetSphere();
        break;

    case 'E':
    case 'e':
        PlaySound(TEXT("salir.wav"), NULL, SND_ASYNC | SND_FILENAME);
        Sleep(3000);
        exit(0);
    }
    glutPostRedisplay();

}


int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed para nÃºmeros aleatorios

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Aiming Game");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glutKeyboardFunc(keyboardCallback);
    generateNewTargetSphere();  // Generar la primera esfera
    cargarTextura(data, 0); 
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseCallback);

    PlaySound(TEXT("inicio.wav"), NULL, SND_ASYNC | SND_FILENAME);
    glutMainLoop();

    return 0;
}
