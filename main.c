#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>

#define WHEIGHT 720
#define WWIDTH 1080
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();
    glRectf(8, -4, 9, 4);
    glRectf(-8, 4, -9, -4);

    glFlush();
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
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WWIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WHEIGHT) / 2);

    glutInitWindowSize(WWIDTH, WHEIGHT);

    glutCreateWindow("XD");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return EXIT_SUCCESS;
}