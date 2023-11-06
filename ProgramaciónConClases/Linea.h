#pragma once
#include <GL/freeglut.h>
class LineDrawer {
    //constructor
public:
    LineDrawer(float _startX, float _startY, float _endX, float _endY)
        :startX(_startX), startY(_startY), endX(_endX), endY(_endY), colorR(1.0f), colorG(1.0f), colorB(1.0f), thik(1) {}
    ///metodods
    void Draw() const {
        glLineWidth(thik);
        glColor3f(colorR, colorG, colorB);
        glBegin(GL_LINES);
        glVertex2f(startX, startY);
        glVertex2f(endX, endY);
        glEnd();

    }
    void SetColor(float r, float g, float b) {
        colorR = r;
        colorG = g;
        colorB = b;
    }

    void SetThik(float ancho) {
        thik = ancho;
    }
    //atributos


private:
    float startX, startY;
    float endX, endY;
    float colorR, colorG, colorB;
    float thik;
};