#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 
using namespace std;
//textura Pared
GLuint textura[2];
int width=800, height=600, nrChannels;

unsigned char* DataParedTextura= stbi_load("Image.jpg", &width, &height, &nrChannels, 0);
unsigned char* dataTechoTextura = stbi_load("Image2.jpg", &width, &height, &nrChannels, 0);

GLfloat esferaX = 0.0f;
GLfloat esferaZ = 0.6f;
GLfloat esferaY = -1.0f;

void cargarTextura(unsigned char* archivo, int index) {

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glGenTextures(1, &textura[index]);
    glBindTexture(GL_TEXTURE_2D, textura[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, archivo);
    stbi_image_free(archivo);

}

void DrawParedes() {
   
    glBegin(GL_QUADS);
    // Cara frontal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Cara posterior
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

    // Cara izquierda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Cara derecha
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

    // Cara superior
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Cara inferior
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

    glEnd();
}

void DrawTecho() {
  
    glBegin(GL_TRIANGLES);

    // Cara frontal
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 1.4f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f, 0.4f, 0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.6f, 0.4f, 0.6f);

    // Cara derecha
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 1.4f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.6f, 0.4f, 0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.6f, 0.4f, -0.6f);

    // Cara de atras
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 1.4f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.6f, 0.4f, -0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.6f, 0.4f, -0.6f);

    // Cara izquierda
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 1.4f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f, 0.4f, -0.6f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.6f, 0.4f, 0.6f);

    glEnd();
}
void DrawEsfera() {
    if (esferaY >= -0.5 && esferaY <= 1.5 && esferaZ <= 0.5 && esferaZ >= -0.5 && esferaX >= -0.5 && esferaX <= 0.5) {
        glColor4f(1, 0, 0, 0.3);
    }
    else
    {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //desabilitar color
    }
    glTranslatef(esferaX, esferaY, esferaZ);
    glutSolidSphere(0.1, 20, 20);
}
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(1.0f, 1.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);  
    //Cubo
    glBindTexture(GL_TEXTURE_2D, textura[0]);  // Aplica la textura
    DrawParedes();
    //Piramide
    glBindTexture(GL_TEXTURE_2D, textura[1]);
    DrawTecho();
    glPopMatrix();
    //Esfera
    //glDisable(GL_TEXTURE_2D);  // Disable texturing
    glPushMatrix();
    DrawEsfera();
   // glEnable(GL_TEXTURE_2D);  
    glPopMatrix();
    glutSwapBuffers();
}

  void keyboard(unsigned char key, int x, int y) {
        switch (key) {
        case 'a':
            esferaX -= 0.1f;
            break;
        case 'd':
            esferaX += 0.1f;
            break;
        case 'w':
            esferaY += 0.1f;
            break;
        case 's':
            esferaY -= 0.1f;
            break;
        case 'z':
            esferaZ += 0.1f;
            break;
        case 'x':
            esferaZ -= 0.1f;
            break;
        }
        glutPostRedisplay();
    }


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,width / height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(20, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Examen U3 VacaGabriel");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(keyboard);
    cargarTextura(DataParedTextura, 0);
    cargarTextura(dataTechoTextura, 1);
    glutDisplayFunc(Draw);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}