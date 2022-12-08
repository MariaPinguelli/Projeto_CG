#include "pipe.h"

void pipe(float width, float height){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    // x1 e y1, coordenadas do vértice superior esquerdo
    // x2 e y2, coordenadas do vértice inferior direito
    glRectf(-1.0, -0.4, -0.7, -1.0);
    glutSwapBuffers();
}