#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>

#define WHEIGHT 720
#define WWIDTH 1080

bool isCollidingPalet1(float x, float y, float *rectv, float *rectv2)
{
    return (x == rectv[0] && y >= rectv[1] && y <= rectv2[1]) ? true : false;
}
bool isCollidingPalet2(float x, float y, float *rectv, float *rectv2)
{
    return (x == rectv[0] && y <= rectv[1] && y >= rectv2[1]) ? true : false;
}
float x = 0, y = 0;
float rect1v[] = {9, -2}, rect1v2[] = {9.5, 2}, rect2v[] = {-9, 2}, rect2v2[] = {-9.5, -2};
float speed = 0.125;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw
    glPointSize(30.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();

    x += speed;
    if (isCollidingPalet1(x, y, rect1v, rect1v2) || isCollidingPalet2(x, y, rect2v, rect2v2))
    {
        speed = -speed;
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
    glutReshapeFunc(reshape);

    glutMainLoop();

    return EXIT_SUCCESS;
}