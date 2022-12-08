#include <GL/glut.h>
#include "main.h"

void display(void){
    pipe(0.4, -0.4);
}

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Hello World");

    setup();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}