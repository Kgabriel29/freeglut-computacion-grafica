#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 600
#define BLOCK_SIZE 30

int speed = 500;
bool pausa = FALSE;
int gradosRotacion = 0;
bool gameOver = false;


struct Figura {
    int bloque[4][4];
    float color[3];
};

Figura figura[7] = {
    { { {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0} }, {1.0f, 0.0f, 0.0f} }, // I
    { { {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {0.0f, 1.0f, 0.0f} }, // O
    { { {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {0.0f, 0.0f, 1.0f} }, // L
    { { {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {1.0f, 1.0f, 0.0f} }, // J
    { { {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {0.0f, 1.0f, 1.0f} }, // Z
    { { {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {1.0f, 0.0f, 1.0f} }, // S
    { { {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} }, {0.0f, 0.5f, 1.0f} }, // T
};

int rejilla[20][10];
int actualFigura;
int currentX, currentY;
int score;
void reiniciarJuego() {
    // Reiniciar los valores de la rejilla
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            rejilla[i][j] = 0;
        }
    }

    // Generar una nueva pieza aleatoria y ubicarla en la posición inicial
    actualFigura = rand() % 7;
    currentX = 5;
    currentY = 17;
    // Reiniciar la puntuación
    score = 0;
    // Reiniciar los grados de rotación
    gradosRotacion = 0;

    glutPostRedisplay();
}

void Bloque(int x, int y, float color[3]) {
    // Coordenadas del bloque en píxeles
    float x1 = static_cast<float>(x) * BLOCK_SIZE;
    float y1 = static_cast<float>(y) * BLOCK_SIZE;
    float x2 = static_cast<float>(x + 1) * BLOCK_SIZE;
    float y2 = static_cast<float>(y + 1) * BLOCK_SIZE;

    // Dibujar el bloque relleno
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawGrid() {
    // Dibujar las líneas de cuadrícula utilizando la función DDA
    glColor3f(0.0f, 0.0f, 0.0f);

    // Dibujar líneas verticales
    for (float x = 0; x <= WINDOW_WIDTH; x += BLOCK_SIZE) {
        glBegin(GL_LINES);
        glVertex2f(x, 0);
        glVertex2f(x, WINDOW_HEIGHT);
        glEnd();
    }

    // Dibujar líneas horizontales
    for (float y = 0; y <= WINDOW_HEIGHT; y += BLOCK_SIZE) {
        glBegin(GL_LINES);
        glVertex2f(0, y);
        glVertex2f(WINDOW_WIDTH, y);
        glEnd();
    }
    // Dibujar las figuras según el tiempo
    glColor3f(1.0f, 0.0f, 0.0f);
    Figura current = figura[actualFigura];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current.bloque[i][j] != 0) {
                int x = currentX + j;
                int y = currentY + i;
                Bloque(x, y, current.color);
            }
        }
    }
    // Dibujar los bloques fijos al llegar a la colisión
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (rejilla[i][j] != 0) {
                float ColorActual[3];
                for (int i = 0; i < 3; ++i) {
                    ColorActual[i] = current.color[i];
                }
                Bloque(j, i, ColorActual);
            }
        }
    }
}


void drawScore() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, 570);   // Posición en la que se encuentra

    // Crear una cadena de texto que combine la puntuación y la velocidad
    char scoreString[50];
    snprintf(scoreString, 50, "Score: %d   Speed: %d", score, speed);

    for (int i = 0; scoreString[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreString[i]);
    }
}

bool VerificarColision(int x, int y, int bloque[4][4]) {
    cout << "verificar colisicon funcionando" << endl;
    // Verificar si hay colisión entre la pieza actual y la cuadrícula en las nuevas coordenadas
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (bloque[i][j] != 0) {
                int newX = x + j;
                int newY = y + i;

                if (newX < 0 || newX >= 10 || newY < 0 || newY >= 20 || rejilla[newY][newX] != 0) {
                    return true; // Colisión detectada
                }
            }
        }
    }
    return false; // Sin colisión
}

void DesplazarFigura(int deltaX, int deltaY) {
    cout << "desplazar figura funcionando" << endl;
    // Mueve la pieza actual horizontalmente (deltaX) y verticalmente (deltaY)
    if (!VerificarColision(currentX + deltaX, currentY + deltaY, figura[actualFigura].bloque)) {
        currentX += deltaX;
        currentY += deltaY;
        cout << "funcion dezplazar" << endl;

    }
    glutPostRedisplay();
}

void Rotar() {
    // Copiar la pieza actual para realizar la rotación temporalmente
    Figura temp = figura[actualFigura];

    // Algoritmo para rotar la pieza actual 90 grados en sentido horario
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp.bloque[i][j] = figura[actualFigura].bloque[3 - j][i];
        }
    }

    // Verificar si la rotación es válida (sin colisión)
    if (!VerificarColision(currentX, currentY, temp.bloque)) {
        cout << "rotar" << endl;
        // Si es válida, copiar la rotación temporal de vuelta a la pieza actual
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                figura[actualFigura].bloque[i][j] = temp.bloque[i][j];
            }
        }

    }

    glutPostRedisplay();
}
void BotarFigura() {

    // Hace caer la pieza actual automáticamente hasta que encuentre un bloque o el límite inferior
    while (!VerificarColision(currentX, currentY - 1, figura[actualFigura].bloque)) {
        currentY--;
        cout << "funcion botarfigura funcionando" << endl;

    }
    glutPostRedisplay();
}

void NewFigura() {
    int newPiece = rand() % 7;

    // Verificar si la nueva pieza es diferente de la pieza actual


    actualFigura = newPiece;
    currentX = 5;

    // Ajustar la posición en función de la altura de la pieza
    currentY = 16; // Comenzar desde la fila más alta

    while (VerificarColision(currentX, currentY, figura[actualFigura].bloque)) {
        currentY++;
        cout << "currentY en newfigura: " << currentY << endl;
        cout << "funcion newfigura" << endl;
        if (currentY == 18) {
            return;

        }

    }
}

void RecortarBloque(Figura* bloque, int recorteX, int recorteY, int recorteWidth, int recorteHeight) {//controla que bajen los bloques no recortados
    cout << "funcion recortar bloque funcionando" << endl;
    int bloqueRecortado[4][4] = { 0 };
    int bloquesRecortados = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Coordenadas del bloque de la figura en la cuadrícula
            int x = currentX + j;
            int y = currentY + i;

            // Verificar si el bloque está dentro de la región de recorte
            if (x >= recorteX && x < recorteX + recorteWidth && y >= recorteY && y < recorteY + recorteHeight) {
                // Copiar el bloque a la nueva figura recortada
                bloqueRecortado[i][j] = bloque->bloque[i][j];
                bloquesRecortados++;
            }
        }
    }

    // Actualizar la Figura original con la Figura recortada
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            bloque->bloque[i][j] = bloqueRecortado[i][j];
        }
    }
}

// Función para eliminar las filas completas después de dibujar los bloques
void eliminarFila() {
    cout << "funcion elminarfila funcionando" << endl;
    for (int i = 0; i < 20; i++) {
        bool lineComplete = true;
        for (int j = 0; j < 10; j++) {
            if (rejilla[i][j] == 0) {
                lineComplete = false;
                break;
            }
        }

        if (lineComplete) {

            // Eliminar la línea completa y mover las líneas superiores hacia abajo
            for (int k = i; k < 19; k++) {
                for (int j = 0; j < 10; j++) {
                    rejilla[k][j] = rejilla[k + 1][j];
                }
            }
            // Llenar la última fila con ceros
            for (int j = 0; j < 10; j++) {
                rejilla[19][j] = 0;
            }
        }
    }
}

void update(int value) {
    cout << "funcion update bien" << endl;
    if (currentY <= 17) {

        if (!pausa && !gameOver) {
            cout << "current y: " << currentY << endl;
            // Controlar el movimiento automático hacia abajo de la pieza actual
            if (!VerificarColision(currentX, currentY - 1, figura[actualFigura].bloque)) {
                currentY--;
                cout << "while dentro de update" << endl;
            }
            else {
                cout << "entra if dentro de la funcion update " << endl;
                // La pieza ha llegado al límite inferior o ha chocado con otra pieza
                // Fijar la pieza actual en la cuadrícula y generar una nueva pieza
                Figura current = figura[actualFigura];
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (current.bloque[i][j] != 0) {
                            int x = currentX + j;
                            int y = currentY + i;
                            rejilla[y][x] = actualFigura + 1; // Usamos valores mayores a 0 para representar las piezas en la cuadrícula
                        }
                    }
                }

                // Verificar si alguna línea está completa y eliminarla
                int lineasEliminadas = 0;
                for (int i = 0; i < 20; i++) {
                    bool lineComplete = true;
                    for (int j = 0; j < 10; j++) {
                        if (rejilla[i][j] == 0) {
                            lineComplete = false;
                            break;
                        }
                    }

                    if (lineComplete) {
                        // Eliminar la línea completa y mover las líneas superiores hacia abajo
                        for (int k = i; k < 19; k++) {
                            for (int j = 0; j < 10; j++) {
                                rejilla[k][j] = rejilla[k + 1][j];
                            }
                        }
                        lineasEliminadas++;
                    }
                }

                // Actualizar la puntuación según las líneas completadas
                switch (lineasEliminadas) {
                case 1:
                    score += 100;
                    if (speed >= 0) {
                        speed = speed - 30;
                    }
                    cout << "elimina 1" << endl;
                    break;
                case 2:
                    score += 250;
                    if (speed >= 0) {
                        speed = speed - 50;
                    }
                    cout << "elimina 2" << endl;
                    break;
                case 3:
                    score += 400;
                    cout << "elimina 3" << endl;
                    if (speed <= 0) {
                        speed = speed - 80;
                    }
                    break;
                case 4:
                    score += 800;
                    break;
                }

                // Eliminar las filas completas nuevamente después de eliminar las piezas
                eliminarFila();
                if (currentY < 17) {
                    NewFigura();
                }
            }

            glutPostRedisplay();
            glutTimerFunc(speed, update, 0); // Llamar a update nuevamente en 500 milisegundos
        }
        else {
            cout << "game over: " << gameOver << endl;
        }
    }
    else {
        cout << "no entra if" << endl;
        cout << "currenty : " << currentY << endl;
        gameOver = true;
        glutPostRedisplay();

    }

}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver) {
        // Dibujar los bloques fijos en la cuadrícula
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (rejilla[i][j] != 0) {
                    float color[3] = { 0.7f, 0.7f, 0.7f };
                    Bloque(j, i, color);
                }
            }
        }

        // Dibujar las figuras actuales
        Figura current = figura[actualFigura];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (current.bloque[i][j] != 0) {
                    int x = currentX + j;
                    int y = currentY + i;
                    Bloque(x, y, current.color);
                }
            }
        }

        // Dibujar la cuadrícula
        drawScore();
        drawGrid();
    }
    else {
        // Mostrar solo el puntaje y el mensaje de reinicio
        drawScore();
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(WINDOW_WIDTH / 2 - 130, WINDOW_HEIGHT / 2);
        const char* gameOverMessage = "Juego Terminado.";
        for (int i = 0; gameOverMessage[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, gameOverMessage[i]);
        }
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        glRasterPos2f(WINDOW_WIDTH / 2 - 130, (WINDOW_HEIGHT / 2) + 20);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Game Over");
    }

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {

    if (!gameOver) {
        switch (key) {
        case 'w': // Tecla W (rotar la pieza)
            Rotar();
            break;
        case 'a': // Tecla A (mover la pieza hacia la izquierda)
            DesplazarFigura(-1, 0);
            break;
        case 'd': // Tecla D (mover la pieza hacia la derecha)
            DesplazarFigura(1, 0);
            break;
        case ' ': // Tecla Espacio (botar la figura)
            BotarFigura();
            break;
        case 'p':
        case 'P': // Tecla P (pausar o reanudar el juego)
            pausa = !pausa;
            if (pausa) {
                speed = 1000000; // Detener el movimiento de la pieza
            }
            else {
                speed = 500; // Volver a la velocidad normal
                glutTimerFunc(speed, update, 0); // Reiniciar el temporizador para el movimiento automático
            }
            break;
        case 'r':
        case 'R':
            // Reiniciar el juego en cualquier momento
            reiniciarJuego();
            cout << "juego reiniciado" << endl;
            gameOver = false; // Reiniciar el estado de gameOver
            break;
        }
    }
}




void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            rejilla[i][j] = 0;
        }
    }

    actualFigura = rand() % 7;
    currentX = 5;
    currentY = 17;
    score = 0;
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(450, 50);
    glutCreateWindow("Tetris");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);


    glutMainLoop();

    return 0;
}