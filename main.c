#include <GL/glew.h>
#include <GL/glut.h>
#include "main.h"
#include "./textures-hands-on/stb-master/stb_image.h"
#include "./textures-hands-on/stb-master/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION

// Variáveis para criação do fundo
int altura = 800, largura = 800;

// void background()
// {
//     int width, height, channels;
//     unsigned char *img = stbi_load("./images/background.png", &width, &height, &channels, 0);
//      stbi_write_jpg("./images/background.png", width, height, channels, img, 100);
// }

void display(void)
{
    pipe(0.4, -0.4);
}

void setup()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // background();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Flappy Bird");

    setup();
    glutDisplayFunc(display);
    // glutDisplayFunc(background);

    glutMainLoop();
    return 0;
}