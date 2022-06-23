#include <time.h>
#include <stdlib.h>
#include "glut.h"

int N = 30, M = 20;
int Scale = 25;

int w = Scale * N;
int h = Scale * M;

int dir, num = 4;

class Snake
{
public:
    int x;
    int y;
};

Snake snake[100];

class Fruit
{
public:
    int x, y;

    void New()
    {
        x = rand() % N;
        y = rand() % M;
    }

    void DrawApple()
    {
        glColor3f(0.0, 1.0, 0.0);
        glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
    }

};

Fruit fruits[10];

void DrawSnake()
{
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < num; i++)
    {
        glRectf(snake[i].x * Scale, snake[i].y * Scale, (snake[i].x + 0.9) * Scale, (snake[i].y + 0.9) * Scale);
    }
}

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    if (dir == 0) snake[0].y += 1;
    if (dir == 1) snake[0].x -= 1;
    if (dir == 2) snake[0].x += 1;
    if (dir == 3) snake[0].y -= 1;

    for (int i = 0; i < 10; i++)
        if ((snake[0].x == fruits[i].x) && (snake[0].y == fruits[i].y))
        {
            num++; fruits[i].New();
        }

    if (snake[0].x > N) dir = 1;  if (snake[0].x < 0) dir = 2;
    if (snake[0].y > M) dir = 3;  if (snake[0].y < 0) dir = 0;

    for (int i = 1; i < num; i++)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)  num = i;
}



void DrawField()
{
    glColor3f(0.0, 0.7, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < w; i += Scale)
    {
        glVertex2f(i, 0); glVertex2f(i, h);
    }
    for (int j = 0; j < h; j += Scale)
    {
        glVertex2f(0, j); glVertex2f(w, j);
    }
    glEnd();
}


void Display() {

    glClear(GL_COLOR_BUFFER_BIT);

    DrawField();

    DrawSnake();

    for (int i = 0; i < 10; i++)
        fruits[i].DrawApple();

    glFlush();
    glutSwapBuffers();
}

void KeyboardEvent(int key, int a, int b)
{
    switch (key)
    {
    case 101:
        dir = 0;
            break;
    case 102:
        dir = 2;
            break;
    case 100:
        dir = 1;
            break;
    case 103:
        dir = 3;
            break;
    }
}

void Timer(int = 0)
{
    Display();

    Tick();

    glutTimerFunc(50, Timer, 0);
}

int main(int argc, char** argv) {

    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        fruits[i].New();
    }
        


    snake[0].x = 10;
    snake[0].y = 10;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow("Test");
    glClearColor(1.0, 1.0, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glutDisplayFunc(Display);
    glutSpecialFunc(KeyboardEvent);
    glutTimerFunc(50, Timer, 0);

    glutMainLoop();
}
