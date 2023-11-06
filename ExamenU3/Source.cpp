//#include <iostream>
//#include <stdlib.h>
//#include <GL/glut.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h" 
//using namespace std;
//
////textura Pared
//
//GLuint textura[2];
//int width=800, height=600, nrChannels;
//
//GLfloat posZ = -1.5f, posX = 0.0f, posY = -2.0f;
//
//unsigned char* textura1= stbi_load("pared.jpg", &width, &height, &nrChannels, 0);
//unsigned char* textura2 = stbi_load("techo.jpg", &width, &height, &nrChannels, 0);
//
//void cargarTextura(unsigned char* archivo, int index) {
//
//    glShadeModel(GL_FLAT);
//    glEnable(GL_DEPTH_TEST);
//    glGenTextures(1, &textura[index]);
//    glBindTexture(GL_TEXTURE_2D, textura[index]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, archivo);
//    stbi_image_free(archivo);
//
//}
//void initRendering() {
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING); // Habilitar el cálculo de iluminación
//    glEnable(GL_LIGHT0); // Habilitar la primera luz (índice 0)
//
//    // Definir los parámetros de la luz ambiental
//    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.0f, 1.0f }; // Color amarillo
//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
//
//    glEnable(GL_COLOR_MATERIAL); // Habilitar seguimiento de color con iluminación
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//}
//
//void  esfera() {
//	glTranslatef(posX, posY, posZ);	
//	glutSolidSphere(0.2, 10, 10);
//
//    if (posY >= -1.5 && posY <= 1.6) {
//        glEnable(GL_LIGHT0); // Activar la luz ambiental 
//    }
//    else {
//        glDisable(GL_LIGHT0); // Desactivar la luz ambiental
//     }
//    glutPostRedisplay();
//    }
//
//
//void handleKeypress(unsigned char key, int x, int y) {
//	switch (key) {
//	case 'w':
//		posY += 0.1f;
//        glutPostRedisplay();
//		break;
//	case 's':
//		posY -= 0.1f;
//        glutPostRedisplay();
//		break;
//	}
//    glutPostRedisplay();
//}
//
//void handleResize(int w, int h) {
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
//}
//
//void Paredes() {
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.1, 0.0);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.1, 0.0);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.0);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.575, 0.0);
//    glEnd();
//
//    // Draw back wall
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.1, 0.5);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.1, 0.5);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.575, 0.5);
//    glEnd();
//
//    // Draw left wall
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.1, 0.0);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2, 0.1, 0.5);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.575, 0.0);
//    glEnd();
//
//    // Draw right wall
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.9, 0.1, 0.0);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.1, 0.5);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.9, 0.575, 0.0);
//    glEnd();
//}
//
//void Techo() {
//    // Front roof
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2, 0.575, 0.0);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.0);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.55, 0.8, 0.25);  // Punto superior de la pirámide
//    glEnd();
//
//    // Back roof
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2, 0.575, 0.5);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.55, 0.8, 0.25);  // Punto superior de la pirámide
//    glEnd();
//
//    // Left roof
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2, 0.575, 0.0);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.55, 0.8, 0.25);  // Punto superior de la pirámide
//    glEnd();
//
//    // Right roof
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.9, 0.575, 0.0);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.55, 0.8, 0.25);  // Punto superior de la pirámide
//    glEnd();
//
//    // Base of the roof
//    glBegin(GL_POLYGON);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.575, 0.0);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.575, 0.0);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9, 0.575, 0.5);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.575, 0.5);
//    glEnd();
//}
//
//void drawScene() {
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//    gluLookAt(1.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);// activar textura
//	glBindTexture(GL_TEXTURE_2D, textura[0]);  // Aplica la textura
//	Paredes();
//	glBindTexture(GL_TEXTURE_2D, textura[1]); // Aplica la textura
//	Techo();
//	glPopMatrix();
//	//dibujar esfera
//	glPushMatrix();
//	glDisable(GL_TEXTURE_2D);
//	esfera();
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(1000, 800);
//	glutCreateWindow("Casa 3D");
//    glEnable(GL_DEPTH_TEST);
//	cargarTextura(textura1, 0);
//    cargarTextura(textura2, 1);
//    initRendering();
//	glutDisplayFunc(drawScene);
//	glutKeyboardFunc(handleKeypress);
//	glutReshapeFunc(handleResize);
//	glutMainLoop();
//	return 0;
//}