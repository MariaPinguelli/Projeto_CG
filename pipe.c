#include "pipe.h"

float randomPipeHeight(){
    float num = 0;

    num = randomNum()*-1;

    return num;
}

void pipe(float width, float height){
    float gap = 0.8;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    // x1 e y1, coordenadas do vértice superior esquerdo
    float x1 = -1.0;
    float y1 = -0.4;
    
    // x2 e y2, coordenadas do vértice inferior direito
    float x2 = -0.7;
    float y2 = -1.0;

    glRectf(x1, y1, x2, y2);

    x1+=0.8;
    y1 = randomPipeHeight();
    x2+=0.8;
    
    glRectf(x1, y1, x2, y2);

    x1+=0.8;
    y1 = randomPipeHeight();
    x2+=0.8;
    
    glRectf(x1, y1, x2, y2);

    x1 = -1.0;
    y1 = 0.4;
    
    x2 = -0.7;
    y2 = 1.0;

    glRectf(x1, y1, x2, y2);

    x1+=0.8;
    y1 = 0.4;
    x2+=0.8;
    
    glRectf(x1, y1, x2, y2);

    x1+=0.8;
    y1 = 0.73;
    x2+=0.8;
    
    glRectf(x1, y1, x2, y2);


    glutSwapBuffers();
}