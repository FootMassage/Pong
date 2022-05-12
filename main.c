#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>

#define WHEIGHT 720
#define WWIDTH 1080
/*Declaracion de variables globales*/
GLfloat x = 0, y = 0;
GLfloat rect1v[] = {9, -2}, rect1v2[] = {9.5, 2}, rect2v[] = {-9, 2}, rect2v2[] = {-9.5, -2};
GLfloat xspeed = 0.125;
GLfloat yspeed = 0.125;
GLfloat pointSize = 30.0;
GLint redScore = 0;
GLint blueScore = 0;
GLfloat speedPalets = 0.45;
GLboolean keystates[256];
/*Checkeo de colisiones*/
bool isCollidingPalet1()
{
    return (x > rect1v[0] - (pointSize / 100) && y > rect1v[1] - (pointSize / 100) && y < rect1v2[1] + (pointSize / 100));
}
bool isCollidingPalet2()
{
    return (x < rect2v[0] + (pointSize / 100) && y < rect2v[1] + (pointSize / 100) && y > rect2v2[1] - (pointSize / 100));
}
bool isCollidingWalls()
{
    return (y == 10 || y == -10);
}
bool redScored()
{
    return (x <= -10);
}
bool blueScored()
{
    return (x >= 10);
}
/*Checkeo de goles*/
void checkGoals()
{
    if (redScored())
    {
        redScore++;
        x = 0;
        y = 0;
        printf("Red score= %d\n", redScore);
    }
    if (blueScored())
    {
        blueScore++;
        x = 0;
        y = 0;
        printf("Blue score= %d\n", blueScore);
    }
}
/*Movimiento de las paletas*/
void checkMov(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'W':
    case 'w':
        rect2v[1] += speedPalets;
        rect2v2[1] += speedPalets;
        keystates['w'] = true;
        keystates['W'] = true;
        break;
    case 'S':
    case 's':
        rect2v[1] -= speedPalets;
        rect2v2[1] -= speedPalets;
        keystates['s'] = true;
        keystates['S'] = true;
        break;
    case 'I':
    case 'i':
        rect1v[1] += speedPalets;
        rect1v2[1] += speedPalets;
        keystates['i'] = true;
        keystates['I'] = true;
        break;
    case 'K':
    case 'k':
        rect1v[1] -= speedPalets;
        rect1v2[1] -= speedPalets;
        keystates['k'] = true;
        keystates['K'] = true;
    default:
        break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    checkGoals();

    // draw
    glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth(2);
    glPointSize(pointSize);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();

    x += xspeed;
    y += yspeed / 2;
    if (isCollidingPalet1() || isCollidingPalet2())
    {
        xspeed = -xspeed;
    }
    if (isCollidingWalls())
    {
        yspeed = -yspeed;
    }

    glColor3f(1.0, 0.0, 0.0);
    glRectfv(rect1v, rect1v2);
    glColor3f(0.0, 0.0, 1.0);
    glRectfv(rect2v, rect2v2);
    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WWIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WHEIGHT) / 2);

    glutInitWindowSize(WWIDTH, WHEIGHT);

    glutCreateWindow("Pong");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(checkMov);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return EXIT_SUCCESS;
}