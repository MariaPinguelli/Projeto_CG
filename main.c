#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define MAX 24
#define FRICCAO_PAREDE 0.6f

// gcc main.c -o main -lglut -lGLU -lGL -lm

// Definição dos tipos de iluminação
GLfloat Light_Pos[] = {0.0f, -20.0f, 80.0f, 0.0f};
GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

float Acceleration = 0.03f;
float Camera = 28.0f;
float x, y, ax, ay, vx, vy;
int a, b;
int direcaoHorizontal = -1, direcaoVertical = -1;
char moveHorizontal = 0, moveVertical = 0;
int anguloMinimo[] = {2, -2}, anguloMaximo[] = {30, -30};

int labirinto[MAX][MAX] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void loadLabirinto()
{
    // Cria nossa tabela de base para o labirinto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 50.0);
    glTranslatef(0.0f, 0.0f, -Camera);
    glRotatef(-0.6f * a, 0.0f, 1.0f, 0.0f);
    glRotatef(0.6f * b - 30, 1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    // Acelera o movimento da bolinha no eixo x ou y
    // usamos PI para suavizar o movimento considerando que ela se movimente em 180 graus
    ax = -Acceleration * sin(a * 2.0f / 180);
    ay = -Acceleration * sin(b * 2.0f / 180);
}

// Carrega os elementos
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    loadLabirinto();
    glLoadIdentity();
    glColor3f(0.5f, 0.0f, 1.0f);

    // Carrega nosso fundo do labirinto
    glBegin(GL_QUADS);
    glVertex2f(-12.0f, -12.0f);
    glVertex2f(12.0f, -12.0f);
    glVertex2f(12.0f, 12.0f);
    glVertex2f(-12.0f, 12.0f);
    glEnd();

    // Carrega nossas paredes
    glEnable(GL_LIGHTING);
    glCallList(1);
    glLoadIdentity();
    glTranslatef(x, y, 0.5f);
    glutSolidSphere(0.5, 40, 40);
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSwapBuffers();
}

// Inicializa a posição da bolinha e os cubos
void init()
{
    glClearColor(0.0f, 0.0, 0.0, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT0, GL_POSITION, Light_Pos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0f);
    // Cria nossa lista de exibição que são os cubos que formam as paredes
    glNewList(1, GL_COMPILE);
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (labirinto[i][j] == 0)
            {
                glLoadIdentity();
                // Desenha os cubos conforme os valores de i e j
                // e a disposição da tabela de fundo
                glTranslatef(-11.5f + j, -11.5f + i, 0.5f);
                glutSolidCube(1.0);
            }
        }
    }
    glEndList();
    // indica as posições que a bolinha deve estar no início
    x = y = 10.0f;
}

void Timer(int value)
{
    int tmp, i, j, j2, k;
    // Recebe a posição atual da bolinha
    vx += ax;
    vy += ay;
    
    // Caso a bolinha fique parada em uma parede no eixo x
    if (vx > 0) {
        // Soma a posição de y em j
        j = (int)(y + 11.6f);
        j2 = (int)(y + 12.4f);
        k = (int)vx;
        tmp = (int)(x + 43.5f) - 30;
        for (i = 0; i < k; i++) {
            if (!labirinto[j][tmp] || !labirinto[j2][tmp])
                break;
            tmp++;
        }
        if (i == k) {
            tmp = (int)(x + vx + 42.5f) - 30;
            if (labirinto[j][tmp] && labirinto[j2][tmp])
                i++;
        }
        if (i > k) {
            x += vx;
        }else {
            x = (int)(x + i + 25) - 24.5f;
            // Permite que a bolinha se mova de forma suave conforme sua disposição
            vx *= -FRICCAO_PAREDE;
        }
    }
    else {
        j = (int)(y + 11.6f);
        j2 = (int)(y + 12.4f);
        k = -(int)vx;
        tmp = (int)(x + 40.5f) - 30;
        for (i = 0; i < k; i++) {
            if (!labirinto[j][tmp] || !labirinto[j2][tmp])
                break;
            tmp--;
        }
        if (i == k) {
            tmp = (int)(x + vx + 41.5f) - 30;
            if (labirinto[j][tmp] && labirinto[j2][tmp])
                i++;
        }
        if (i > k) {
            x += vx;
        } else {
            x = (int)(x - i + 25) - 24.5f;
            vx *= -FRICCAO_PAREDE;
        }
    }

    // Caso a bolinha fique parada em uma parede no eixo y
    if (vy > 0) {
        j = (int)(x + 11.6f);
        j2 = (int)(x + 12.4f);
        k = (int)vy;
        tmp = (int)(y + 43.5f) - 30;
        for (i = 0; i < k; i++) {
            if (!labirinto[tmp][j] || !labirinto[tmp][j2])
                break;
            tmp++;
        }
        if (i == k){
            tmp = (int)(y + vy + 42.5f) - 30;
            if (labirinto[tmp][j] && labirinto[tmp][j2])
                i++;
        }
        if (i > k)
            y += vy;
        else {
            y = (int)(y + i + 25) - 24.5f;
            vy *= -FRICCAO_PAREDE;
        }
    } else {
        j = (int)(x + 11.6f);
        j2 = (int)(x + 12.4f);
        k = -(int)vy;
        tmp = (int)(y + 40.5f) - 30;
        for (i = 0; i < k; i++) {
            if (!labirinto[tmp][j] || !labirinto[tmp][j2])
                break;
            tmp--;
        }
        if (i == k) {
            tmp = (int)(y + vy + 41.5f) - 30;
            if (labirinto[tmp][j] && labirinto[tmp][j2])
                i++;
        }
        if (i > k) {
            y += vy;
        } else {
            y = (int)(y - i + 25) - 24.5f;
            vy *= -FRICCAO_PAREDE;
        }
    }
    // Faz o movimento da bolinha no eixo vertical ou horizontal em relação ao labirinto
    if (direcaoHorizontal > -1) {
        if (a == 0) {
            if (!moveHorizontal)
                direcaoHorizontal = -1;
            else
                a += anguloMinimo[direcaoHorizontal];
        } else if (a != anguloMaximo[direcaoHorizontal])
            a += anguloMinimo[direcaoHorizontal];
    }
    if (direcaoVertical > -1) {
        if (b == 0) {
            if (!moveVertical)
                direcaoVertical = -1;
            else
                b += anguloMinimo[direcaoVertical];
        }
        else if (b != anguloMaximo[direcaoVertical])
            b += anguloMinimo[direcaoVertical];
    }
    glutPostRedisplay();
    // Suaviza o movimento da bolinha
    glutTimerFunc(25, Timer, 0);
}

void teclas(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        direcaoHorizontal = 0;
        moveHorizontal = 1;
        break;
    case GLUT_KEY_RIGHT:
        direcaoHorizontal = 1;
        moveHorizontal = 1;
        break;
    case GLUT_KEY_DOWN:
        direcaoVertical = 0;
        moveVertical = 1;
        break;
    case GLUT_KEY_UP:
        direcaoVertical = 1;
        moveVertical = 1;
        break;
    }
}

// Faz a leitura da tecla
void zoom(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
    {
        if (Camera > 24.0f)
            Camera -= 1.0f;
    }
    else if (key == 'w' || key == 'W')
    {
        if (Camera < 36.0f)
            Camera += 1.0f;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Demonstra que as paredes são compostas por cubos
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(350, 60);
    glutCreateWindow("Labirinto");

    // Desenha os cubos e desenha a bolinha
    init();
    glutSpecialFunc(teclas);
    glutKeyboardFunc(zoom);

    // Responsável pelo movimento do tabuleiro
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(display);
    glutMainLoop();
}
