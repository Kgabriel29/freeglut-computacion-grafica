#include <GL/freeglut.h>
class SphereDrawer {
	//constructor
public:
	SphereDrawer()
		:posX(0.0f), posY(0.0f), posZ(0.0f), colorR(1.0f), colorG(1.0f), colorB(1.0f), radius(0.1f) {}
	//metodos
	void Draw() const{
		glColor3f(colorR, colorG, colorB);
		glTranslatef(posX, posY, posZ);
		glutSolidSphere(radius, 10, 10);
	}
	void SetColor(float r, float g, float b) {
		colorR = r;
		colorG = g;
		colorB = b;
	}
	void SetRadio(float radio) {
		radius = radio;
	}
	void setPosition(float x, float y, float z) {
		posX = x;
		posY = y;
		posZ = z;
	}
	//atributos

private:
	float posX, posY, posZ;
	float colorR, colorG, colorB;
	float radius;
};