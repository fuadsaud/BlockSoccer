#include "Includes.h"

#include "Person.h"
#include "Camera.h"
#include "Scene.h"

void init();
void display();
void background(int n);
void keyboard(unsigned char key, int x, int y);
void passiveMotion(int x, int y);

Scene scene;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BlockSoccer");

    init();

    background(100);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glViewport(0, 0, 800, 600);

    scene.init();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    scene.display();

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    scene.keyboard(key, x, y);
}

void passiveMotion(int x, int y)
{
    scene.passiveMotion(x, y);
}

void background(int time)
{
    scene.background();

    glutPostRedisplay();

    glutTimerFunc(time, background, time);
}
