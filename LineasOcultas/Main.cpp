#include <GL/freeglut.h>

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Triángulo
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireSphere(1,30,30);

	// Triángulo 2
	glColor3f(1.0f, 0.0f, 1.0f);
	glTranslatef(0, 0,-3);
	glutSolidSphere(0.4, 200, 200);


	glutSwapBuffers();
}

void Init() {


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(20, 1.0f, 1.0, 20.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	1.0, 1.0, 10.0, 
				0, 0, 0, 
				1, 1, 0);
	glClearColor(0, 0, 0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glOrtho(-1, 1, -1, 1, 1, -1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Lineas Ocultas");
	Init();

	glutDisplayFunc(Display);
	glutMainLoop();
}
